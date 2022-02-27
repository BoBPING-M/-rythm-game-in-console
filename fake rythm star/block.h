#ifndef BLOCK_H_
#define BLOCK_H_
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <list>
#include <string>
#include "gameSize.h"


enum class juge
{ 
	nope, //키입력 없을시
	per,
	exc,
	goo,
	hmm,
	fail
};

class Block //블록
{
private:
	COORD pos;
	clock_t speed; //블록 속도
	clock_t spawnTime; //블록 생성 시간;
public:
	Block() : speed(0), spawnTime(0) { pos.X = 0; pos.Y = 3; }
	Block(clock_t isp,int ix, int iy = 3) : speed(isp) { pos.X = ix; pos.Y = iy; spawnTime = clock(); }
	~Block() {}
	void setSpawn() { spawnTime = clock(); }
	bool setSpeed(clock_t sp); //스피드 설정 함수
	juge putScore(clock_t inputT, int& score, int& combo); //점수 넣음
	COORD& returnPos() { return pos; }
	clock_t spawnVal() { return spawnTime; }
	clock_t speedVal() { return speed; }
	juge move(int & score, int & combo); //y좌표 이동 블럭 성공시 y좌표 리턴, 실패시 -1 리턴
};

class needMove //블록이 이동해야 하는지 판단하는 functor
{
private:
	int& score;
	int& combo;
public:
	needMove() = delete;
	needMove(int& sc, int& cbo) : score(sc), combo(cbo) {}
	~needMove() {}
	juge operator()(Block* bl);
};

struct waitingBlock //대기열 저장 정보
{
	Block* temp; //블록 정보
	clock_t go; //시작 시간
};

clock_t readBlock(std::string s, std::list<waitingBlock*>* wait);
void GoBlock(std::list<Block*>* now, std::list<waitingBlock*>* wait, int ix, std::mutex & m);

#endif