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
#endif // !DISP_H_

/*
	const int ySize = 80;
	const int xSize = 59;*/