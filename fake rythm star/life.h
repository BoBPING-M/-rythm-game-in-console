#ifndef LIFE_H_
#define LIFE_H_

#include <iostream>
#include "display.h"

class Life
{
private :
	int cur; //현재 체력
	const static int max = 10; //최대 체력

public:
	Life() : cur(5) {}
	Life(int l) : cur(l) {}
	~Life() {}
	int returnCur() { return cur; }
	const int returnMax() { return max; }
	void lifedown() { if(cur > 0) cur--; }
	void lifeup() { if(cur < 10) cur++; }
};


#endif // !LIFE_H_
