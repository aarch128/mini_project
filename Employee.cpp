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
	cout << "职工编号：" << this->m_id << "\t";
	cout << "职工姓名：" << this->m_name << "\t";
	cout << "职工岗位：" << this->GetDeptName() << endl;
}
string Employee::GetDeptName()
{
	return string("职工");
}