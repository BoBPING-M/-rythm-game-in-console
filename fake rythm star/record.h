#ifndef RECORD_H_
#define RECORD_H_
#include <string>
#include <vector>

const int MAX_NAME_LEN = 3;

class Record
{
private:
	std::string name; //이름
	int rec;//점수
public:
	Record(); //디폴트 생성자
	Record(std::string nm, int score) : name(nm), rec(score) {}; //매개변수 이용한 생성자
	~Record() {} //디폴트 파괴자
	bool inputInfo(int score); //정보 입력 (키보드로 입력) 정상 입력시 true, 비정상 입력시 false 반환
	const std::string& returnName() { return name; }
	const int& returnRec() { return rec; }
};

void writeRecord(int score, std::vector<Record>& rec);

void readRecord(std::vector<Record>& rec);

#endif // !RECORD_H_
