#include "sound.h"
#include <iostream>

MCI_OPEN_PARMS openBGM; //브금노래파일을 열기위한 정보 저장 구조체
MCI_PLAY_PARMS playBGM; //브금노래 재생시 정보 저장 구조체
MCI_SEEK_PARMS seekBGM; //브금 노래 재 지정시 정보 저장 구조체
int dwID; //브금 디바이스 아이디 저장용

void setBgm() //브금 세팅용 함수
{
	openBGM.lpstrElementName = (LPCWSTR)L"D:\\OneDrive\\C++\\fake rythm star\\fake rythm star\\TEST\\TEST.mp3"; //파일 오픈 구조체에 파일 경로 지정 
	openBGM.lpstrDeviceType = (LPCWSTR)L"mpegvideo"; //파일 형식 지정(mp3 지정)
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)&openBGM); //openBGM 구조체의 정보로 노래 오픈
	dwID = openBGM.wDeviceID;//openBGM의 디바이스 아이디 저장
}

void playingBgm()
{
	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)&playBGM); //음악 재생
}

void resetBgm() //게임 클리어 시 노래 재지정
{
	mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)&seekBGM);
}

void stopBgm() //음악 스탑용
{
	mciSendCommand(dwID, MCI_STOP, NULL, (DWORD_PTR)nullptr); //MCI_STOP은 음악을 정지하고 시작지점으로 돌려버림
}

Mci * setBoom(LPCWSTR file) //효과음 세팅 함수
{
	Mci* tmci = new Mci{ new MCI_OPEN_PARMS , new MCI_PLAY_PARMS, new MCI_SEEK_PARMS };
	tmci->mo->lpstrElementName = file;
	tmci->mo->lpstrDeviceType = (LPCWSTR)L"mpegvideo";
	mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD_PTR)tmci->mo); //오픈시 구조체에 노래 파일 유형과 경로가 포함되어 있다고 알리는 옵션으로 실행
	return tmci;
}

void playingBoom(int dwID, MCI_PLAY_PARMS * playBoom) //효과음 재생 함수
{
	mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD_PTR)playBoom); //MCI_NOTIFY 옵션은 처리 결과를 저장하는 옵션인데 당장 불필요한 옵션이라 NULL을 전달해도 이상X
}

void goToStartBoom(int dwID, MCI_SEEK_PARMS * seekBoom)
{
	mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD_PTR)seekBoom); //노래의 시작 지점으로 돌리는 옵션
}