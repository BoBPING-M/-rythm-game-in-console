#include "sound.h"
#include <iostream>

MCI_OPEN_PARMS openBGM; //��ݳ뷡������ �������� ���� ���� ����ü
MCI_PLAY_PARMS playBGM; //��ݳ뷡 ����� ���� ���� ����ü
MCI_SEEK_PARMS seekBGM; //��� �뷡 �� ������ ���� ���� ����ü
int dwID; //��� ����̽� ���̵� �����

void setBgm() //��� ���ÿ� �Լ�
{
	openBGM.lpstrElementName = (LPCWSTR)L"D:\\OneDrive\\C++\\fake rythm star\\fake rythm star\\TEST\\TEST.mp3"; //���� ���� ����ü�� ���� ��� ���� 
	openBGM.lpstrDeviceType = (LPCWSTR)L"mpegvideo"; //���� ���� ����(mp3 ����)
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)&openBGM); //openBGM ����ü�� ������ �뷡 ����
	dwID = openBGM.wDeviceID;//openBGM�� ����̽� ���̵� ����
}

void playingBgm()
{
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