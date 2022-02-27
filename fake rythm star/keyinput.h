#ifndef KEYINPUT_H_
#define KEYINPUT_H_
#include "block.h"
#include "life.h"
#include <mutex>

void keyInput(std::list<Block*>*nw, int ix, int & score, int & combo, char k, std::mutex& m, Life & lf);


#endif // !KEYINPUT_H_