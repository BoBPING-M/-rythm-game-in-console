#ifndef RECORD_H_
#define RECORD_H_
#include <string>
#include <vector>

typedef struct RECORD_
{
	std::string name = "";
	int rec = 0;
}Record;

void writeRecord(std::string& name, int score, std::vector<Record>& rec);

void readRecord(std::vector<Record>& rec);

#endif // !RECORD_H_
