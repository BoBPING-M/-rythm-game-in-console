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
	system("mode con: cols=80 lines=35");
	std::wcout.imbue(std::locale("korean")); //�����ڵ� ������ ����
	char keys[6]{ 'S', 'D', 'F', 'J', 'K', 'L' }; //���ӿ� ����� Ű �迭 ���� �� ��� Ű ���� ����
	std::vector<Record> rec; //��� ������
	readRecord(rec);
	printMainScreen();
	while (true) //���θ޴� ����
	{
		if ((GetAsyncKeyState('1') & 0x8001) == 0x8001) //���� ����
		{
			gameStart(keys, rec);
			printDie();
			while (true) //����� ������
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
		if ((GetAsyncKeyState('2') & 0x8001) == 0x8001) //���� ����
		{
			printInfo();
			printMainScreen();
		}
		if ((GetAsyncKeyState('3') & 0x8001) == 0x8001) //���� ���
		{
			printRecord(rec);
			printMainScreen();
		}
		if ((GetAsyncKeyState(VK_BACK) & 0x8001) == 0x8001) //���� �����, �ڷΰ���
			break;
	}
	return 0;
}