#include "sound.h"
#include <iostream>
#include <mutex>

extern bool gameIsRunning;

MCI_OPEN_PARMS openBGM; //��ݳ뷡������ �������� ���� ���� ����ü
MCI_PLAY_PARMS playBGM; //��ݳ뷡 ����� ���� ���� ����ü
MCI_SEEK_PARMS seekBGM; //��� �뷡 �� ������ ���� ���� ����ü
int dwID; //��� ����̽� ���̵� �����
extern HWND winhwnd;
extern HINSTANCE hinstance;


void setBgm() //��� ���ÿ� �Լ�
{
	openBGM.lpstrElementName = (LPCWSTR)L"D:\\OneDrive\\C++\\fake rythm star\\fake rythm star\\TEST\\TEST.mp3"; //���� ���� ����ü�� ���� ��� ���� 
	openBGM.lpstrDeviceType = (LPCWSTR)L"mpegvideo"; //���� ���� ����(mp3 ����)
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)&openBGM); //openBGM ����ü�� ������ �뷡 ����
	dwID = openBGM.wDeviceID;//openBGM�� ����̽� ���̵� ����
}

void playingBgm()
{
	playBGM.dwCallback = (unsigned __int64)winhwnd;
	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&playBGM); //���� ���
}

void resetBgm() //���� Ŭ���� �� �뷡 ������
{
	mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)&seekBGM);
}

void stopBgm() //���� ��ž��
{
	mciSendCommand(dwID, MCI_STOP, NULL, (DWORD_PTR)nullptr); //MCI_STOP�� ������ �����ϰ� ������������ ��������
}

Mci * setBoom(LPCWSTR file) //ȿ���� ���� �Լ�
{
	Mci* tmci = new Mci{ new MCI_OPEN_PARMS , new MCI_PLAY_PARMS, new MCI_SEEK_PARMS };
	tmci->mo->lpstrElementName = file;
	tmci->mo->lpstrDeviceType = (LPCWSTR)L"mpegvideo";
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)tmci->mo); //���½� ����ü�� �뷡 ���� ������ ��ΰ� ���ԵǾ� �ִٰ� �˸��� �ɼ����� ����
	return tmci;
}

void playingBoom(int dwID, MCI_PLAY_PARMS * playBoom) //ȿ���� ��� �Լ�
{
	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)playBoom); //MCI_NOTIFY �ɼ��� ó�� ����� �����ϴ� �ɼ��ε� ���� ���ʿ��� �ɼ��̶� NULL�� �����ص� �̻�X
}

void goToStartBoom(int dwID, MCI_SEEK_PARMS * seekBoom)
{
	mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)seekBoom); //�뷡�� ���� �������� ������ �ɼ�
}

void endBgm(std::mutex & m) //������ ������ ���������� ���� ����
{
	while (gameIsRunning == true)
	{
		if (playBGM.dwCallback == MCI_NOTIFY_SUCCESSFUL)
		{
			m.lock();
			gameIsRunning = false;
			m.unlock();
		}
	}
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT imessage, WPARAM wparam, LPARAM lparam)
{
	using namespace std;
	switch (imessage)
	{
	case WM_CREATE:
		break;
	case MM_MCINOTIFY:
		switch (wparam)
		{
		case MCI_NOTIFY_SUCCESSFUL:
			gameIsRunning = false;
			break;
		default:
			break;
		}
		break;
	case WM_DESTROY:
		break;
	}
	return DefWindowProc(hwnd, imessage, wparam, lparam);
}
