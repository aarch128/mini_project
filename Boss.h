#pragma once
#include<iostream>
#include<string>
#include"Worker.h"
using namespace std;
class Boss : public Worker
{
public:
	Boss(int , string , int);
	void ShowInfo();
	string GetDeptName();
};