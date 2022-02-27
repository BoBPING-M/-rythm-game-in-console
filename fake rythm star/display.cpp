#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <mutex>
#include <vector>
#include "record.h"
#include "display.h"
#include "block.h"
#include "life.h"

extern bool gameIsRunning;

void printBlock(Block * bl)
{
	setInputPo(bl);//해당 블럭 좌표 재 이동
	std::wcout << L"├──────┤"; //블럭 출력

	setInputPo(0, ySize + 1);
}

void deleteBlock(Block* bl)
{
	setInputPo(bl); //해당 블럭 좌표로 입력 위치 이동
	if (bl->returnPos().Y == 2)
		return;
	std::cout << "        "; //해당 위치 초기화
	if (bl->returnPos().Y == ySize)
		printBackGround();

	setInputPo(0, ySize + 1);
}

void setInputPo(Block* bl)
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), bl->returnPos());
}

void setInputPo(int x, int y)
{
	COORD pos{0,0};
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void printCombo(int combo, juge jg) //콤보 출력
{
	setInputPo(xSize + 5, 20);
	std::cout << "     ";
	setInputPo(xSize + 5, 21);
	for (int i = 0; i < 10; i++)
		std::cout << ' ';
	if (jg != juge::nope && jg != juge::fail)
	{
		setInputPo(xSize + 5, 20);
		std::cout << "COMBO";
		setInputPo(xSize + 5, 21);
		std::cout << combo;
	}
	setInputPo(0, ySize + 1);
}

void printScore(int score)
{
	setInputPo(xSize + 9, 3);
	for (int i = 0; i < 10; i++) //부분 초기화
		std::cout << ' ';
	setInputPo(xSize + 9, 3);
	std::cout << "SCORE : " << score;
	setInputPo(0, ySize + 1);
}

void printJuge(juge jg)
{
	setInputPo(xSize + 5, 30);
	for (int i = 0; i < 12; i++)
		std::cout << ' ';
	setInputPo(xSize + 5, 30);
	switch (jg)
	{
	case juge::nope:
		break;
	case juge::per:
		std::cout << "PERFECT!";
		break;
	case juge::exc:
		std::cout << "EXCELLENT!";
		break;
	case juge::goo:
		std::cout << "GOOD!";
		break;
	case juge::hmm:
		std::cout << "hmm..";
		break;
	case juge::fail:
		std::cout << "fail....";
		break;
	}
	setInputPo(0, ySize + 1);
}

void printBackGround()
{
	setInputPo(1, 2);
	std::wcout << L"┌";
	for (int i = 2; i < xSize; i++)
		std::wcout << L"─";
	std::wcout << L"┐";
	for (int i = 3; i < ySize; i++)
	{
		setInputPo(1, i);
		std::wcout << L"│";
		setInputPo(xSize, i);
		std::wcout << L"│";
	}
	setInputPo(2, ySize-2);
	std::wcout << L"─";
	setInputPo(xSize - 1, ySize - 2);
	std::wcout << L"─";
	setInputPo(1, ySize);
	std::wcout << L"└";
	for (int i = 2; i < xSize; i++)
		std::wcout << L"─";
	std::wcout << L"┘";
	setInputPo(0, ySize + 1);
}

void printAllBlock(std::list<Block*>* nw)
{
	//사전 블럭 제거
	for (int i = 0; i < 6; i++)
		std::for_each(nw[i].begin(), nw[i].end(), deleteBlock);
	//다시 블럭 프린트
	for (int i = 0; i < 6; i++)
		std::for_each(nw[i].begin(), nw[i].end(), printBlock);
	setInputPo(0, ySize + 1);
}

void printGameScreen(Block * bl, int score, int combo, juge jg)
{
	//현재 블럭 없애기
	deleteBlock(bl);
	//점수 출력
	printScore(score);

	//콤보 출력
	printCombo(combo, jg);

	//판정 출력
	printJuge(jg);

	setInputPo(0, ySize + 1);
}

void movePrint(std::list<Block*>* nw,int ix, int&score, int&combo, std::mutex & m, Life & lf) //게임 시작 시 켜지는 함수 각 블럭을 계속 점검해 시간이 되면 블럭을 이동시킴
{
	Block* temp;
	while (true)
	{
		m.lock();
		if (gameIsRunning == true)
		{
			if (nw[ix].size() != 0)
			{
				if (needMove(score, combo)((*(nw[ix].begin()))) == juge::fail) //블록이 터지는 곳
				{
					temp = *(nw[ix].begin());
					nw[ix].erase(nw[ix].begin());
					delete temp;
					lf.lifedown();
					printLife(lf);
					printJuge(juge::fail);
					printCombo(combo, juge::fail);
				}
				if (lf.returnCur() == 0)
				{
					gameIsRunning = false;
					m.unlock();
					return;
				}
				std::for_each(nw[ix].begin(), nw[ix].end(), needMove(score, combo));
			}
		}
		else
		{
			m.unlock();
			return;
		}
		m.unlock();
	}
}

void printLife(Life & lf)
{
	int i = 1;
	setInputPo(xSize + 2, 3);
	std::cout << "LIFE";
	setInputPo(xSize + 3, 4);
	for (i; i <= lf.returnMax() - lf.returnCur(); i++)
	{
		std::wcout << L"□";
		setInputPo(xSize + 3, 4 + i);
	}
	for (i; i <= lf.returnMax(); i++)
	{
		std::wcout << L"■\n";
		setInputPo(xSize + 3, 4 + i);
	}
	setInputPo(0, ySize + 1);
}

void printMainScreen()
{
	using std::cout;
	using std::endl;
	system("cls"); //메인 화면 출력 전 초기화
	setInputPo(xSize / 2 - 4, ySize / 2 - 10);
	cout << "조잡한 리듬게임";
	setInputPo(xSize / 2 - 4, ySize / 2 - 6);
	cout << "1.게임 시작\n";
	setInputPo(xSize / 2 - 4, ySize / 2 - 4);
	cout << "2.게임 설명\n";
	setInputPo(xSize / 2 - 4, ySize / 2 - 2);
	cout << "3.기록 보기\n";
	setInputPo(xSize / 2 - 4, ySize / 2);
	cout << "종료";
	setInputPo(0, ySize + 1);
}

void printInfo()
{
	using std::cout;
	using std::endl;
	system("cls");
	cout << "정보창\n";
	cout << "정보가 있을예정\n";
	while ((GetAsyncKeyState(VK_BACK) & 0x8001) != 0x8001)
		continue;
}

void printRecord(std::vector<Record> & rec)
{
	using std::cout;
	using std::endl;
	system("cls");
	int i = 1;
	for (auto ptr = rec.begin(); ptr != rec.end(); ptr++)
	{
		cout << i++ << "등. " << (*ptr).name << endl;
		cout << "점수 : " << (*ptr).rec << endl;
	}
	while ((GetAsyncKeyState(VK_BACK) & 0x8001) != 0x8001)
		continue;
}

void printDie()
{
	setInputPo(xSize / 2 - 3, ySize / 2 -2);
	std::cout << "YOU DIE!";
	setInputPo(xSize / 2 - 2, ySize / 2);
	std::cout << "RETRY?";
	setInputPo(xSize / 2 - 3, ySize / 2 + 2);
	std::cout << "(Y / N)";
}

void printWait()
{
	for (int i = 5; i > 0; i--)
	{
		setInputPo(xSize / 2-1, ySize / 2);
		std::cout << i;
		Sleep(600);
	}
	setInputPo(xSize / 2 - 3, ySize / 2);
	std::cout << "START!";
	Sleep(600);
	setInputPo(xSize / 2 - 3, ySize / 2);
	std::cout << "      ";
	setInputPo(0, ySize+1);
}