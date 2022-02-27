#ifndef SOUND_H_
#define SOUND_H_

#include <Windows.h>
#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>
#include <Digitalv.h>


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

#endif // !SOUND_H_