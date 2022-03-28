#ifndef SOUND_H_
#define SOUND_H_

#include <Windows.h>
#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>
#include <Digitalv.h>
#include <mutex> 
#include <Vfw.h>


typedef struct Mci_
{
	MCI_OPEN_PARMS* mo;
	MCI_PLAY_PARMS* mp;
	MCI_SEEK_PARMS* ms;
}Mci;

void setBgm();

void playingBgm();

void resetBgm();

void stopBgm();

Mci * setBoom(LPCWSTR file);

void playingBoom(int dwID, MCI_PLAY_PARMS* playBoom);

void goToStartBoom(int dwID, MCI_SEEK_PARMS* seekBoom);

void endBgm(std::mutex& m);

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam); //노래 관리용


#endif // !SOUND_H_