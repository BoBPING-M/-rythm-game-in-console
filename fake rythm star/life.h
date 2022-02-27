#ifndef LIFE_H_
#define LIFE_H_

#include <iostream>
#include "display.h"

class Life
{
private :
	int cur; //���� ü��
	const static int max = 10; //�ִ� ü��

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
