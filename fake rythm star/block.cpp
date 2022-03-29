#include <iostream>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <string>
#include <mutex>
#include "block.h"
#include "display.h"

extern bool gameIsRunning;

juge Block::putScore(clock_t inputT, int& score, int& combo)
{
	if (inputT == 0) //블록이 터져야 할때
	{
		combo = 0;
		return juge::fail;
	}
	clock_t timeDif = abs(inputT - (spawnTime + speed * (ySize - 3))); //입력시간과 블록생성 도착시간간 차이 절댓값
	if (timeDif < speed * 2.5)
	{
		score += (100 + (++combo / 10));
		return juge::per;
	}
	else if (timeDif < speed * 3)
	{
		score += (75 + (++combo / 3));
		return juge::exc;
	}
	else if (timeDif < speed * 3.5)
	{
		score += (50 + (++combo / 20));
		return juge::goo;
	}
	else if (timeDif < speed * 4)
	{
		++combo;
		score += (25);
		return juge::hmm;
	}
	else //입력을 개 거지같이 했을때
	{
		combo = 0;
		return juge::fail;
	}
}

juge Block::move(int& score, int& combo)
{
	pos.Y++;
	if (pos.Y >= ySize)
		return putScore(0, score, combo); //Y좌표가 증가해 YMAX가되면 블럭이 터지니 점수 제공
	return juge::nope; //그냥 이동하는 판정
}

bool Block::setSpeed(clock_t sp)
{
	speed = sp;
	return true;
}

juge needMove::operator()(Block* bl)
{
	if (((clock() - bl->spawnVal()) / bl->speedVal()) > (bl->returnPos().Y - 3))
	{
		deleteBlock(bl);
		if (bl->move(score, combo) == juge::fail)
			return juge::fail;
		else
			printBlock(bl);
	}
	return juge::nope;
}

clock_t readBlock(std::string s, std::list<waitingBlock*>* wait) //블록 대기 데이터 입력
{
	std::ifstream blocks;
	int line; //라인 읽기용 변수
	clock_t speed; //스피드 읽기용 변수
	clock_t goT; //시작 시간 이전 블럭과 차이 시간 ex) A1블럭이 400 클럭에 나오고 이 시간이 400 이면 A2블럭은 800 클럭에 나옴
	waitingBlock* temp; //대기열에 넣을 임시 정보
	blocks.open(s, std::ios_base::in | std::ios_base::binary);
	if (!blocks.is_open())
	{
		std::cerr << "블록 데이터가 읽어지지 않습니다.\n";
		exit(EXIT_FAILURE);
	}
	blocks.read((char*)&speed, sizeof speed);
	while (!blocks.eof())
	{
		temp = new waitingBlock;
		blocks.read((char*)&line, sizeof line);
		blocks.read((char*)&goT, sizeof goT);
		if (blocks.eof())
		{
			delete temp;
			break;
		}
		temp->temp = new Block(speed, line * 9 + 4);
		temp->go = goT;
		wait[line].push_back(temp);
	}
	blocks.close();
	return speed;
}


void GoBlock(std::list<Block*>* now, std::list<waitingBlock*>* wait, int ix, std::mutex & m)
{
	clock_t preBlockT = clock();
	waitingBlock* temps;
	while (true)
	{
		if (wait[ix].size() <= 0)
			return;
		if (wait[ix].size() >= 0)
		{
			if (clock() > ((*(wait[ix].begin()))->go + preBlockT))
			{
				temps = *(wait[ix].begin());
				wait[ix].erase(wait[ix].begin());
				temps->temp->setSpawn();
				preBlockT = clock();
				m.lock();
				now[ix].push_back(temps->temp);
				printBlock(*(now[ix].rbegin()));
				m.unlock();
				delete temps;
			}
		}
		m.lock();
		if (gameIsRunning == false)
		{
			m.unlock();
			return;
		}
		m.unlock();
	}
}