#define _CRT_SECURE_NO_WARNINGS
#include"Manager.h"
using namespace std;
Manager::Manager(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_dept_id = did;
}
void Manager::ShowInfo()
{
	cout << "ְ����ţ�" << this->m_id << "\t";
	cout << "ְ��������" << this->m_name << "\t";
	cout << "ְ����λ��" << this->GetDeptName() << endl;
}
string Manager::GetDeptName()
{
	return string("����");
}