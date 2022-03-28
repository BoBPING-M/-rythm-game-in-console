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
#include <tchar.h>
#include <WinUser.h>

CONST TCHAR* lpszClass = _T("Consol Test!\n");
HWND winhwnd;
HINSTANCE hinstance;

bool gameIsRunning = false;

int main()
{
	using std::thread;

	WNDCLASS wndclass;
	SetConsoleTitle(lpszClass);
	hinstance = GetModuleHandle(NULL);

	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = NULL;
	wndclass.hCursor = NULL;
	wndclass.hIcon = NULL;
	wndclass.hInstance = hinstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = lpszClass;
	wndclass.lpszMenuName = NULL;
	wndclass.style = NULL;
	RegisterClass(&wndclass);
	winhwnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hinstance, NULL);

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
		if ((GetAsyncKeyState('4') & 0x8001) == 0x8001) //Ű ����
		{
			printSetting(keys);
			printMainScreen();
		}
		if ((GetAsyncKeyState(VK_BACK) & 0x8001) == 0x8001) //���� �����, �ڷΰ���
			break;
	}
	return 0;
}

