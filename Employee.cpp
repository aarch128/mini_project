#define _CRT_SECURE_NO_WARNINGS
#include"Employee.h"
using namespace std;
Employee::Employee(int id, string name, int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_dept_id = did;
}
void Employee::ShowInfo()
{
	cout << "ְ����ţ�" << this->m_id << "\t";
	cout << "ְ��������" << this->m_name << "\t";
	cout << "ְ����λ��" << this->GetDeptName() << endl;
}
string Employee::GetDeptName()
{
	return string("ְ��");
}