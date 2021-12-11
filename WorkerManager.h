#pragma once
#include<iostream>
#include<string>
#include"Boss.h"
#include"Employee.h"
#include"Manager.h"
#include"Worker.h"
#include<fstream>
#include<string.h>
#define EMP_FILE "EmpFile.txt"
using namespace std;
class WorkerManager
{
public:
	WorkerManager();
	~WorkerManager();
	void ShowMenu();
	void Exit();
	int m_worker_num;
	Worker** m_worker_arr;
	bool m_empty_file_flag;
	int GetEmpNum();
	void InitEmp();
	void AddWorker();
	void DelEmp();
	void ModEmp();
	void Find();
	void FindById();
	void FindByName();
	void Sort();
	void Save();
	int IfIdExisted(int id , Worker ** new_worker_arr , int temp_len);
	void Print();
	void Clean();

};