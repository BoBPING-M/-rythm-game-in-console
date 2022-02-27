#include <iostream>
#include <thread>
#include <list>
#include <vector>
#include <algorithm>
#include <mutex>
#include <fstream>
#include "block.h"
#include "display.h"
#include "keyinput.h"
#include "sound.h"
#include "life.h"
#include "gameRunning.h"
#include "record.h"




bool gameIsRunning = false;

int main()
{
	using std::thread;
	gameIsRunning = false;
	system("mode con: cols=80 lines=40");
	std::wcout.imbue(std::locale("korean")); //유니코드 로케일 변경
	const char keys[6]{ 'S', 'D', 'F', 'J', 'K', 'L' }; //게임에 사용할 키 배열 변경 시 사용 키 변경 가능
	std::vector<Record> rec; //기록 보관용
	readRecord(rec);


	/*using std::ios_base;
	Record temp;
	std::ifstream fin;
	fin.open("D:\\OneDrive\\C++\\fake rythm star\\fake rythm star\\record\\record.dat", ios_base::in | ios_base::binary);
	if (!fin.is_open())
	{
		std::cerr << "파일이 열리지 않음";
		exit(EXIT_FAILURE);
	}
	while (!fin.eof())
	{
		fin.read((char*)&(temp.name), sizeof(temp.name));
		fin.read((char*)&(temp.rec), sizeof(temp.rec));
		if (fin.eof())
			break;
		rec.push_back(temp);
	}
	fin.close();*/


	printMainScreen();
	while (true) //메인메뉴 선택
	{
		if ((GetAsyncKeyState('1') & 0x8001) == 0x8001) //게임 시작
		{
			gameStart(keys, rec);
			printDie();
			while (true) //재시작 선택지
			{
				if ((GetAsyncKeyState('Y') & 0x8001) == 0x8001)
				{
					gameStart(keys, rec);
					printDie();
					continue;
				}
				else if ((GetAsyncKeyState('N') & 0x8001) == 0x8001)
				{
					break;
				}
			}
			printMainScreen();
		}
		if ((GetAsyncKeyState('2') & 0x8001) == 0x8001) //게임 설명
		{
			printInfo();
			printMainScreen();
		}
		if ((GetAsyncKeyState('3') & 0x8001) == 0x8001) //게임 기록
		{
			printRecord(rec);
			printMainScreen();
		}
		if ((GetAsyncKeyState(VK_BACK) & 0x8001) == 0x8001) //게임 종료시, 뒤로가기
			break;
	}
	return 0;
}