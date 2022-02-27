#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "record.h"
#include "display.h"



bool operator<(const Record & r1, const Record & r2)
{
	if (r1.rec < r2.rec)
		return true;
	else
		return false;
}

void writeRecord(std::string& name, int score, std::vector<Record> & rec)
{
	using std::ios_base;
	using std::vector;
	Record temp{ name, score };
	rec.push_back(temp);
	std::sort(rec.begin(), rec.end());
	std::ofstream fout;
	fout.open("D:\\OneDrive\\C++\\fake rythm star\\fake rythm star\\record\\record.dat", ios_base::out | ios_base::app | ios_base::binary);
	if (!fout.is_open())
	{
		std::cerr << "기록 저장 파일을 열지 못했습니다.\n";
		exit(EXIT_FAILURE);
	}
	for (auto pt = rec.begin(); pt != rec.end(); pt++)
	{
		fout.write((char*)&(*pt), sizeof(Record));
	}
	fout.close();
}

void readRecord(std::vector<Record>& rec)
{
	using std::ios_base;
	std::ifstream fin;
	Record temp;
	fin.open("D:\\OneDrive\\C++\\fake rythm star\\fake rythm star\\record\\record.dat", ios_base::in | ios_base::binary);
	if (!fin.is_open())
	{
		return;
	}
	while (!fin.eof())
	{
		fin.read((char*)&(temp), sizeof(temp));
		if (fin.eof())
			break;
		rec.push_back(temp);
	}
	for (auto ptr = rec.begin(); ptr != rec.end(); ptr++)
	{
		std::cout << (*ptr).name << " " << (*ptr).rec << std::endl;
	}
	fin.close();
	//printRecord(rec);
	//std::cout << "test";
}
