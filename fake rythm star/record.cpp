#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "record.h"
#include "display.h"

Record::Record()
{
	name = "AAA";
	rec = 0;
}

bool Record::inputInfo(int score)
{
	using std::cout;
	using std::cin;
	using std::endl;
	std::string temp_n;
	cout << "이름 입력 : ";
	std::getline(cin, temp_n);
	if (temp_n.length() != MAX_NAME_LEN)
		return false;
	else
	{
		name = temp_n;
		name.resize(MAX_NAME_LEN + 1);
		rec = score;
		return true;
	}
}

bool recordCompare(Record & r1, Record & r2) //정렬시 사용할 함수
{
	if (r1.returnRec() > r2.returnRec())
		return true;
	else
		return false;
}

void writeRecord(int score, std::vector<Record> & rec)
{
	using std::ios_base;
	using std::vector;
	using std::string;
	Record temp;
	while (!temp.inputInfo(score))
		continue;
	rec.push_back(temp);
	std::sort(rec.begin(), rec.end(), recordCompare);
	std::ofstream fout;
	fout.open("D:\\OneDrive\\C++\\fake rythm star\\fake rythm star\\record\\record.dat", ios_base::out | ios_base::trunc | ios_base::binary);
	if (!fout.is_open())
	{
		std::cerr << "기록 저장 파일을 열지 못했습니다.\n";
		exit(EXIT_FAILURE);
	}
	for (auto pt = rec.begin(); pt != rec.end(); pt++)
	{
		fout.write((char*)(pt->returnName().c_str()), MAX_NAME_LEN + 1);
		fout.write((char*)&(pt->returnRec()), sizeof(pt->returnRec()));
	}
	fout.close();
}

void readRecord(std::vector<Record>& rec)
{
	using std::ios_base;
	std::ifstream fin;
	std::string temp_n; //이름 임시 객체
	temp_n.resize(MAX_NAME_LEN + 1);
	int temp_s; //점수 임시 변수
	fin.open("D:\\OneDrive\\C++\\fake rythm star\\fake rythm star\\record\\record.dat", ios_base::in | ios_base::binary);
	if (!fin.is_open())
	{
		return;
	}
	while (!fin.eof())
	{
		fin.read((char*)&temp_n[0], MAX_NAME_LEN + 1);
		fin.read((char*)&temp_s, sizeof(temp_s));
		Record temp(temp_n, temp_s);
		if (fin.eof())
			break;
		rec.push_back(temp);
	}
	fin.close();
}
