#ifndef RECORD_H_
#define RECORD_H_
#include <string>
#include <vector>

const int MAX_NAME_LEN = 3;

class Record
{
private:
	std::string name; //�̸�
	int rec;//����
public:
	Record(); //����Ʈ ������
	Record(std::string nm, int score) : name(nm), rec(score) {}; //�Ű����� �̿��� ������
	~Record() {} //����Ʈ �ı���
	bool inputInfo(int score); //���� �Է� (Ű����� �Է�) ���� �Է½� true, ������ �Է½� false ��ȯ
	const std::string& returnName() { return name; }
	const int& returnRec() { return rec; }
};

void writeRecord(int score, std::vector<Record>& rec);

void readRecord(std::vector<Record>& rec);

#endif // !RECORD_H_
