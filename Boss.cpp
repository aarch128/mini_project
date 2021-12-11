#define _CRT_SECURE_NO_WARNINGS
#include"Boss.h"
using namespace std;
Boss :: Boss(int id , string name , int did)
{
	this->m_id = id;
	this->m_name = name;
	this->m_dept_id = did;
}
void Boss::ShowInfo()
{
	cout << "职工编号：" << this->m_id << "\t";
	cout << "职工姓名：" << this->m_name << "\t";
	cout << "职工岗位：" << this->GetDeptName() << endl;
}
string Boss::GetDeptName()
{
	return string("老板");
}