#include <iostream>
#include <Windows.h>
#include <cstdlib>
#include <conio.h>
#include <thread>
#include <list>
#include <mutex>
#include "sound.h"
#include "block.h"
#include "display.h"
#include "gameSize.h"
#include "gameRunning.h"

extern bool gameIsRunning;

void keyInput(std::list<Block*>* nw, int ix, int& score, int& combo, char k, std::mutex& m, Life& lf)
{
	clock_t printKeyTime = LONG_MAX;
	Mci* boom = setBoom((LPCWSTR)L"D:\\OneDrive\\C++\\fake rythm star\\fake rythm star\\effectS\\Boom.mp3");
	juge jg = juge::nope;
	while (1)
	{
		m.lock();
		deletePrintKeyInput(printKeyTime, ix);
		if (gameIsRunning == false)
		{
			m.unlock();
			break;
		}
		m.unlock();
		if ((GetAsyncKeyState(k) & 0x8001) == 0x8001) //k로 전달된 문자와 ix로 전달된 인덱스 값을 이용해 게임 중 동작 시행
		{
			m.lock(); //같은 메모리 사용때문에 락
			printKeyTime = printKeyInput(ix);
			goToStartBoom(boom->mo->wDeviceID, boom->ms); //효과음 시작 지점으로 이동하라
			
			if (nw[ix].size() != 0)
			{
				Block* temp = *(nw[ix].begin()); //없앨 블록 임시 저장소
				nw[ix].erase(nw[ix].begin()); //리스트에서 블럭 없앰
				jg = temp->putScore(clock(), score, combo);
				printGameScreen(temp, score, combo, jg);
				if (jg == juge::fail) //만약 키입력후 판정이 fail이라면
				{
					lf.lifedown(); //라이프를 깍고
					printLife(lf); //라이프를 출력한다
				}
				else //키입력 후 판정이 fail이 아닐경우
				{
					if (combo != 0 && combo % 5 == 0) //콤보가 5의 배수이면(0제외)
					{
						lf.lifeup();
						printLife(lf);
					}
				}
				delete temp;
			}
			playingBoom(boom->mo->wDeviceID, boom->mp); //효과음 재생
			if (lf.returnCur() == 0)
			{
				gameIsRunning = false;
			}
			m.unlock();//락 해제
		}
	}
}
