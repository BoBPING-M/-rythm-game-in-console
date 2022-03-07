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
	using blist = std::list<Block*>; //�� ��ü ������ ����Ʈ
	using thVector = std::vector<std::thread>;
	using wblist = std::list<waitingBlock*>;
	int combo = 0; //�̹� ���� �޺�
	int score = 0; //�̹� ���� ����
	Life lf;
	blist now[6]; //���� �� ���κ� ����Ʈ
	wblist wait[6]; //��� �� ���κ� ����Ʈ
	std::string name = "MSG"; //�̹� ���� �̸�

	readBlock("data.dat", wait);
	std::mutex m; //��������� ������ ħ��?�� �������� ���ؽ�
	thVector key; //Ű �Է��� ���� ��������� �迭
	thVector playing;//�ӵ��� ���� ��� �̵� ������ �迭
	thVector making;

	//���� ���� �� ����
	m.lock();
	printBackGround();
	printScore(score);
	printLife(lf);
	printKeys(keys);
	m.unlock();
	printWait();

	setBgm();
	playingBgm();
	//���� ����
	for (int i = 0; i < 6; i++)
	{
		key.push_back(std::thread(keyInput, now, i, std::ref(score), std::ref(combo), keys[i], std::ref(m), std::ref(lf))); //�� Ű�� ������ ���� �� �۵�
		playing.push_back(std::thread(movePrint, now, i, std::ref(score), std::ref(combo), std::ref(m), std::ref(lf))); //�ӵ��� ���� ��� �̵� ������
		making.push_back(std::thread(GoBlock, now, wait, i, std::ref(m)));
	}

	//���� ����
	for (int i = 0; i < 6; i++)//������ ����
	{
		making[i].join();
		key[i].join();
		playing[i].join(); //���ᰡ �ȵ� 1������
	}
	stopBgm();
	resetBgm();
	gameIsRunning = false;

	//��� ����
	writeRecord(score, rec);
}