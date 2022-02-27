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
	std::wcout.imbue(std::locale("korean")); //�����ڵ� ������ ����
	const char keys[6]{ 'S', 'D', 'F', 'J', 'K', 'L' }; //���ӿ� ����� Ű �迭 ���� �� ��� Ű ���� ����
	std::vector<Record> rec; //��� ������
	readRecord(rec);


	/*using std::ios_base;
	Record temp;
	std::ifstream fin;
	fin.open("D:\\OneDrive\\C++\\fake rythm star\\fake rythm star\\record\\record.dat", ios_base::in | ios_base::binary);
	if (!fin.is_open())
	{
		std::cerr << "������ ������ ����";
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