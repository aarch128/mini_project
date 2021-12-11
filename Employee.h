#pragma once
#include<iostream>
#include<string>
#include"Worker.h"
using namespace std;
class Employee : public Worker
{
public:
	Employee(int, string, int);
	void ShowInfo();
	string GetDeptName();
};