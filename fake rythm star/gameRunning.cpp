#include <iostream>
#include <thread>
#include <list>
#include <vector>
#include <algorithm>
#include <mutex>
#include <string>
#include "block.h"
#include "display.h"
#include "keyinput.h"
#include "sound.h"
#include "life.h"
#include "gameRunning.h"
#include "record.h"

extern bool gameIsRunning;

void gameStart(char * keys, std::vector<Record> &rec)
{
	system("cls");
	gameIsRunning = true;
	using blist = std::list<Block*>; //블럭 객체 포인터 리스트
	using thVector = std::vector<std::thread>;
	using wblist = std::list<waitingBlock*>;
	int combo = 0; //이번 게임 콤보
	int score = 0; //이번 게임 점수
	Life lf;
	blist now[6]; //현재 블럭 라인별 리스트
	wblist wait[6]; //대기 블럭 라인별 리스트
	std::string name = "MSG"; //이번 게임 이름

	readBlock("data.dat", wait);
	std::mutex m; //쓰레드들의 데이터 침범?을 막기위한 뮤텍스
	thVector key; //키 입력을 위한 쓰레드들의 배열
	thVector playing;//속도에 따른 블록 이동 스레드 배열
	thVector making;

	//게임 최초 판 생성
	m.lock();
	printBackGround();
	printScore(score);
	printLife(lf);
	printKeys(keys);
	m.unlock();
	printWait();

	setBgm();
	playingBgm();
	//게임 시작
	for (int i = 0; i < 6; i++)
	{
		key.push_back(std::thread(keyInput, now, i, std::ref(score), std::ref(combo), keys[i], std::ref(m), std::ref(lf))); //각 키별 쓰레드 생성 및 작동
		playing.push_back(std::thread(movePrint, now, i, std::ref(score), std::ref(combo), std::ref(m), std::ref(lf))); //속도에 따른 블록 이동 스레드
		making.push_back(std::thread(GoBlock, now, wait, i, std::ref(m)));
	}

	//게임 종료
	for (int i = 0; i < 6; i++)//쓰레드 종료
	{
		making[i].join();
		key[i].join();
		playing[i].join(); //종료가 안됨 1번부터
	}
	stopBgm();
	resetBgm();
	gameIsRunning = false;

	//기록 저장
	writeRecord(score, rec);
}