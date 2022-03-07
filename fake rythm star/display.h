#ifndef DISP_H_
#define DISP_H_

#include <iostream>
#include <list>
#include <mutex>
#include <vector>
#include "record.h"
#include "block.h"
#include "life.h"
#include "gameSize.h"


void printBlock(Block * bl);//블럭 출력
void deleteBlock(Block* bl);
void setInputPo(Block* bl); //블럭 좌표로 입력 위치 이동
void setInputPo(int x, int y); //x, y좌표로 입력 위치 이동
void printCombo(int combo, juge jg);
void printScore(int score);
void printJuge(juge jg);
void printBackGround();
void printGameScreen(Block * bl, int score, int combo, juge jg); //게임판 출력
void printAllBlock(std::list<Block*>* nw);
void movePrint(std::list<Block*>* nw,int ix, int& score, int& combo, std::mutex & m, Life & lf);
void printLife(Life& lf);
void printMainScreen();
void printInfo();
void printRecord(std::vector<Record> & rec);
void printDie();
void printWait();
void printKeys(char key[6]);
clock_t printKeyInput(int ix); //키 입력시 효과 반환값은 효과를 없애기 위한 시간 비교용
void deletePrintKeyInput(clock_t& st, int ix); //매개변수로 전달된 효과 생성 시간과 현재 시간을 비교해 60클럭이 넘으면 효과 삭제
#endif // !DISP_H_

/*
	const int ySize = 80;
	const int xSize = 59;*/