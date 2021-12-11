#pragma once
#include<iostream>
#include<string>
#include"Worker.h"
using namespace std;
class Manager : public Worker
{
public:
	Manager(int, string, int);
	void ShowInfo();
	string GetDeptName();
};