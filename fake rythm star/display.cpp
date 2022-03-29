#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <mutex>
#include <vector>
#include <string>
#include <iomanip>
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
	setInputPo(2, ySize - 2);
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
	setInputPo(79 / 2 - 6, 34 / 2 - 10);
	cout << "조잡한 리듬게임";
	setInputPo(79 / 2 - 5, 34 / 2 - 6);
	cout << "1.게임 시작\n";
	setInputPo(79 / 2 - 5, 34 / 2 - 4);
	cout << "2.게임 설명\n";
	setInputPo(79 / 2 - 5, 34 / 2 - 2);
	cout << "3.기록 보기\n";
	setInputPo(79 / 2 - 5, 34 / 2);
	cout << "4.키   변경\n";
	setInputPo(79 / 2 - 3, 34 / 2 + 2);
	cout << "<- 종료";
	setInputPo(79 / 2 - 8, 34 / 2 + 9);
	cout << "해당 메뉴 키 입력";
	setInputPo(0, ySize + 1);
}

void printInfo()
{
	using std::cout;
	using std::endl;
	system("cls");
	std::string title = "게임 설명";
	std::string toMain = "<- 메인메뉴로";
	std::string descripton = "설명 귀찮아";
	setInputPo(79 / 2 - ((title.length() / 2) * 2), 2);
	cout << title;
	setInputPo(79 - toMain.length(), 34);
	cout << toMain;
	setInputPo(79/2 - descripton.length(), 34 / 2);
	cout << descripton;
	while ((GetAsyncKeyState(VK_BACK) & 0x8001) != 0x8001)
		continue;
}

void printRecord(std::vector<Record> & rec)
{
	using std::cout;
	using std::endl;
	system("cls");
	const int LISTSIZE = 15; //한 화면에 표시할 랭크 갯수
	int listSize = rec.size() / LISTSIZE + 1; //총 페이지 수
	int rank = 1; //등수
	std::string title = "점수표";
	std::string toMain = "<- 메인메뉴로";
	std::string descripton2 = "PG UP : 이전 페이지 | PG DN : 다음 페이지";
	setInputPo(79/2 - ((title.length() / 2) * 2), 1);
	cout << title;
	setInputPo(79 - toMain.length(), 34);
	cout << toMain;
	setInputPo(0, 34);
	std::cout << descripton2;
	setInputPo(79 - toMain.length() - 8, 34);
	std::cout << "1 / " << listSize;
	for (int i = 0; i < listSize; i++)
	{
		for (int n = 0; n < LISTSIZE; n++)
		{
			if ((LISTSIZE * i) + n == rec.size())
				break;
			setInputPo(79 / 2 - 8, 2*n + 3);
			cout << rank++ << "등. " << rec[(LISTSIZE * i) + n].returnName();
			setInputPo(79 / 2 - 8, 2*n + 4);
			cout << "점수 : " << rec[(LISTSIZE * i) + n].returnRec();
		}
		while (true)
		{
			if ((GetAsyncKeyState(VK_PRIOR) & 0x8001) == 0x8001) //페이지 업키 입력 (앞장으로 넘기기)
			{
				if (i > 0) //첫페이지가 아닐경우
				{
					rank =  (i-1) * LISTSIZE + 1;
					system("cls");
					setInputPo(79 / 2 - ((title.length() / 2) * 2), 1);
					cout << title;
					setInputPo(79 - toMain.length(), 34);
					cout << toMain;
					setInputPo(0, 34);
					std::cout << descripton2;
					setInputPo(79 - toMain.length() - 8, 34);
					std::cout << i << " / " << listSize;
					i -= 2;
					break;
				}
				else //첫페이지 일경우
					continue;
			}
			if ((GetAsyncKeyState(VK_NEXT) & 0x8001) == 0x8001) //페이지 다운키 입력 (뒷장으로 넘기기)
			{
				if (i != listSize - 1) //마지막 페이지가 아닐경우
				{
					system("cls");
					setInputPo(79 / 2 - ((title.length() / 2) * 2), 1);
					cout << title;
					setInputPo(79 - toMain.length(), 34);
					cout << toMain;
					setInputPo(0, 34);
					std::cout << descripton2;
					setInputPo(79 - toMain.length() - 8, 34);
					std::cout << i + 2 << " / " << listSize;
					break;
				}
				else //마지막 페이지일 경우
					continue;
			}
			if ((GetAsyncKeyState(VK_BACK) & 0x8001) == 0x8001) //뒤로가기
				return;
		}
	}
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

void printKeys(char key[6])
{
	for (int i = 0; i < 6; i++)
	{
		setInputPo(9 * (i+1) - 1, ySize + 1);
		std::cout << key[i];
	}
	setInputPo(0, ySize + 1);
}

clock_t printKeyInput(int ix)
{
	setInputPo(9 * ix + 4, ySize + 2);
	std::cout << "■■■■";
	setInputPo(0, ySize + 1);
	return clock();
}

void deletePrintKeyInput(clock_t &st, int ix)
{
	if (clock() - st > 120)
	{
		setInputPo(9 * ix + 4, ySize + 2);
		std::cout << "        ";
		setInputPo(0, ySize + 1);
		st = LONG_MAX;
	}
}

void printSettingDescrip()
{
	std::string title = "키변경";
	std::string toMain = "<- 메인메뉴로";
	std::string descripton1 = "바꿀 키를 누르세요";
	setInputPo(79 / 2 - ((title.length() / 2) * 2), 2);
	std::cout << title;
	setInputPo(79 / 2 - ((descripton1.length() / 2)) - 3, 6);
	std::cout << descripton1;
	setInputPo(79 - toMain.length(), 34);
	std::cout << toMain;
}

void printSetting(char* keys)
{
	using std::cout;
	using std::endl;
	using std::cin;
	system("cls");
	const char* KORNUM[6] = { "첫", "두", "세", "네", "다섯", "여섯" };
	printSettingDescrip();
	for (int i = 0; i < 6; i++)
	{
		setInputPo(79 / 2 - 18, 2*i + 8);
		cout << std::right<< std::setw(10)<< KORNUM[i] << "번째 키 : " << keys[i];
	}
	while (true)
	{
		if ((GetAsyncKeyState(keys[0]) & 0x8001) == 0x8001)
		{
			system("cls");
			setInputPo(79 / 2 - 12, 34 / 2);
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			cout << "변경할 키 입력 : ";
			keys[0] = cin.get();
			if (islower(keys[0]))
				keys[0] = toupper(keys[0]);
			while (cin.get() != '\n')
				continue;
			system("cls");
			printSettingDescrip();
			for (int i = 0; i < 6; i++)
			{
				setInputPo(79 / 2 - 18, 2 * i + 8);
				cout << std::right << std::setw(10) << KORNUM[i] << "번째 키 : " << keys[i];
			}
		}
		if ((GetAsyncKeyState(keys[1]) & 0x8001) == 0x8001)
		{
			system("cls");
			setInputPo(79 / 2 - 12, 34 / 2);
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			cout << "변경할 키 입력 : ";
			keys[1] = cin.get();
			if (islower(keys[1]))
				keys[1] = toupper(keys[1]);
			while (cin.get() != '\n')
				continue;
			system("cls");
			printSettingDescrip();
			for (int i = 0; i < 6; i++)
			{
				setInputPo(79 / 2 - 18, 2 * i + 8);
				cout << std::right << std::setw(10) << KORNUM[i] << "번째 키 : " << keys[i];
			}
		}
		if ((GetAsyncKeyState(keys[2]) & 0x8001) == 0x8001)
		{
			system("cls");
			setInputPo(79 / 2 - 12, 34 / 2);
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			cout << "변경할 키 입력 : ";
			keys[2] = cin.get();
			if (islower(keys[2]))
				keys[2] = toupper(keys[2]);
			while (cin.get() != '\n')
				continue;
			system("cls");
			printSettingDescrip();
			for (int i = 0; i < 6; i++)
			{
				setInputPo(79 / 2 - 18, 2 * i + 8);
				cout << std::right << std::setw(10) << KORNUM[i] << "번째 키 : " << keys[i];
			}
		}
		if ((GetAsyncKeyState(keys[3]) & 0x8001) == 0x8001)
		{
			system("cls");
			setInputPo(79 / 2 - 12, 34 / 2);
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			cout << "변경할 키 입력 : ";
			keys[3] = cin.get();
			if (islower(keys[3]))
				keys[3] = toupper(keys[3]);
			while (cin.get() != '\n')
				continue;
			system("cls");
			printSettingDescrip();
			for (int i = 0; i < 6; i++)
			{
				setInputPo(79 / 2 - 18, 2 * i + 8);
				cout << std::right << std::setw(10) << KORNUM[i] << "번째 키 : " << keys[i];
			}
		}
		if ((GetAsyncKeyState(keys[4]) & 0x8001) == 0x8001)
		{
			system("cls");
			setInputPo(79 / 2 - 12, 34 / 2);
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			cout << "변경할 키 입력 : ";
			keys[4] = cin.get();
			if (islower(keys[4]))
				keys[4] = toupper(keys[4]);
			while (cin.get() != '\n')
				continue;
			system("cls");
			printSettingDescrip();
			for (int i = 0; i < 6; i++)
			{
				setInputPo(79 / 2 - 18, 2 * i + 8);
				cout << std::right << std::setw(10) << KORNUM[i] << "번째 키 : " << keys[i];
			}
		}
		if ((GetAsyncKeyState(keys[5]) & 0x8001) == 0x8001)
		{
			system("cls");
			setInputPo(79 / 2 - 12, 34 / 2);
			FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
			cout << "변경할 키 입력 : ";
			keys[5] = cin.get();
			if (islower(keys[5]))
				keys[5] = toupper(keys[5]);
			while (cin.get() != '\n')
				continue;
			system("cls");
			printSettingDescrip();
			for (int i = 0; i < 6; i++)
			{
				setInputPo(79 / 2 - 18, 2 * i + 8);
				cout << std::right << std::setw(10) << KORNUM[i] << "번째 키 : " << keys[i];
			}
		}
		if ((GetAsyncKeyState(VK_BACK) & 0x8001) == 0x8001)
		{
			return;
		}
	}
}