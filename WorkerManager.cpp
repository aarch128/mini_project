#define _CRT_SECURE_NO_WARNINGS
#include"WorkerManager.h"
using namespace std;
WorkerManager::WorkerManager()
{
	ifstream init_emp_file;
	init_emp_file.open(EMP_FILE, ios::in);

	if (0 == init_emp_file.is_open()) {//文件不存在
		//cout << "empfile is unexisted"<<endl;
		this->m_empty_file_flag = 1;
		this->m_worker_num = 0;
		this->m_worker_arr = NULL;

		init_emp_file.close();
		return;
	}
	char eof_flag = '1';
	init_emp_file >> eof_flag;
	if (1 == init_emp_file.eof()) {//文件存在但无内容
		//cout << "empfile is emptied" << endl;
		this->m_empty_file_flag = 1;
		this->m_worker_num = 0;
		this->m_worker_arr = NULL;
		init_emp_file.close();
		return;
	}
	else {//文件存在内容不为空
		init_emp_file.close();//关闭探测文件是否打开而打开的文件
		int get_file_emp_num = 0;
		this->m_empty_file_flag = 0;
		get_file_emp_num = GetEmpNum();//获取文件中条数
		this->m_worker_num = get_file_emp_num;
		this->m_worker_arr = NULL;
		this->InitEmp();//读取到内存
		
	}
}
WorkerManager :: ~WorkerManager()
{
	if (this->m_worker_arr != NULL) {
		for (int i = 0; i < this->m_worker_num; i++) {
			delete this->m_worker_arr[i];
			this->m_worker_arr[i] = NULL;
		}
		delete this->m_worker_arr;
		this->m_worker_arr = NULL;
	}
}
int WorkerManager::GetEmpNum()//获取文件中信息条数，文件必须存在
{
	ifstream get_emp_num;
	get_emp_num.open(EMP_FILE, ios::in);
	int num = 0;
	char temp[1024] = {'0'};
	while(get_emp_num.getline(temp,sizeof(temp))){//每次读取一行，遇到EOF值为0
		num++;
	}
	get_emp_num.close();
	return num;
}
void WorkerManager::InitEmp()//文件必须存在
{
	enum Position
	{
		employee = 1,
		manager,
		boss
	};
	ifstream init_emp;
	init_emp.open(EMP_FILE, ios::in);
	this->m_worker_arr = new Worker * [this->m_worker_num];

	for (int i = 0; i < this->m_worker_num; i++) {
		int id = 0;
		string name="0";
		int did = 0;
		char tmp[128];
		init_emp>>tmp;//读取id
		id = atoi(tmp);//缓存id
		memset(tmp, 0, 128);
		init_emp >> name;//缓存name
		init_emp >> tmp;//读取did
		did = atoi(tmp);//缓存did
		memset(tmp, 0, 128);
		switch (did) {
		case employee: {
			this->m_worker_arr[i] = new Employee(id, name, 1);
		}
					 break;
		case manager: {
			this->m_worker_arr[i] = new Manager(id, name, 1);
		}
					 break;
		case boss: {
			this->m_worker_arr[i] = new Boss(id, name, 1);
		}
					 break;
		}
	}
	init_emp.close();
}

void WorkerManager :: ShowMenu()
{
	cout << "******************************" << endl;
	cout << "**\t职工管理系统        **" << endl;
	cout << "*\t  0.退出系统         *" << endl;
	cout << "*\t1.增加职工信息       *" << endl;
	cout << "*\t2.显示职工信息       *" << endl;
	cout << "*\t3.删除离职职工       *" << endl;
	cout << "*\t4.修改职工信息       *" << endl;
	cout << "*\t5.查找职工信息       *" << endl;
	cout << "*\t6.按照编号排序       *" << endl;
	cout << "*\t7.清空所有文档       *" << endl;
	cout << "******************************" << endl;
}
void WorkerManager::AddWorker()
{
	enum Options
	{
		employee = 1,
		manager,
		boss
	};
	cout << "输入增加个数:>";
	int add_num = 0;
	cin >> add_num;
	if (add_num > 0) {
		int new_worker_num = this->m_worker_num + add_num;//新员工数量
		Worker** new_worker_arr = new Worker * [new_worker_num];//worker*变量存放于堆区

		if (this->m_worker_arr != NULL) {//旧的worker*数组有数据维护，先将旧员工用临时变量维护
			for (int i = 0; i < this->m_worker_num; i++) {
				new_worker_arr[i] = this->m_worker_arr[i];//将旧的维护指针复制到new_worker_arr[i]
			}
		}//else旧的worker*数组为空
		for (int j = 0; j < add_num; j++) {
			int id = 0;
			string name ="0";
			int did = 0;
			while (1) {
				cout << "输入第(" << j + 1 <<"/"<<add_num << ")个新增成员的编号:>";
				cin >> id;
				if (id < 0) {
					cout << "编号必须是非负整数" << endl;
					continue;
				}
				if (-1 != IfIdExisted(id, new_worker_arr, this->m_worker_num + j)) {
					cout <<endl<< "此编号已被占据，换一个" << endl;
				}
				else {//编号未被占据
					break;
				}
			}
			cout << "输入第(" << j + 1 << "/" << add_num << ")个新增成员的名字:>";
			cin >> name;
			while (1) {
				cout << "选择第(" << j + 1 << "/" << add_num << ")个员工的职位:";
				cout << "(1.职工  2.经理  3.老板)" << endl;
				cout << ":>";
				cin >> did;
				
				if (1 == did || 2 == did || 3 == did) {
					switch (did) {
						case employee: {//从已有的后面开始增加
							new_worker_arr[this->m_worker_num+j] = new Employee(id, name, 1);
							break;
						}
						case manager: {
							new_worker_arr[this->m_worker_num + j] = new Manager(id, name, 2);
							break;
						}
						case boss: {
							new_worker_arr[this->m_worker_num + j] = new Boss(id, name, 3);
							break;
						}
					}
					break;//跳出while
				}
				else {
					cout << endl<<"选择错误，重新选择" << endl;
				}
			}
		}//增加完成
		if (this->m_worker_arr != NULL) {//不能释放旧内存，先置空旧指zhen
			this->m_worker_arr = NULL;
		}
		this->m_worker_arr = new_worker_arr;//复制临时指针数组
		this->m_worker_num = new_worker_num;//继承新人数
		new_worker_arr=NULL;//临时worker*数组置空
	}
	else if (0 == add_num) {
		cout << "人数未增加" << endl;
	}
	else {
		cout << "输入错误" << endl;
	}
	cout << "成功添加" << add_num << "条员工信息，" << "现共有" << this->m_worker_num << "条员工信息" << endl;
	this->Save();
	this->m_empty_file_flag = 0;//保存之后文件为空标志位置0
	system("pause");
	system("cls");
}
void WorkerManager::DelEmp()
{
	if (0 == this->m_worker_num) {
		cout << "暂无员工信息" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "输入要删除员工信息的编号:>";
	int del_id = -1;
	cin >> del_id;
	int ret_set = -1;
	ret_set=this->IfIdExisted(del_id, this->m_worker_arr, this->m_worker_num);
	if (-1 != ret_set) {//编号存在
		cout << "确认删除(y/n):>";
		char yn = 0;
		cin >> yn;
		if ('y' == yn) {
			for (int i = 0; i < this->m_worker_num - ret_set - 1; i++) {
				this->m_worker_arr[ret_set + i]->m_id = this->m_worker_arr[ret_set + i + 1]->m_id;
				this->m_worker_arr[ret_set + i]->m_name = this->m_worker_arr[ret_set + i + 1]->m_name;
				this->m_worker_arr[ret_set + i]->m_dept_id = this->m_worker_arr[ret_set + i + 1]->m_dept_id;
			}
			delete this->m_worker_arr[this->m_worker_num - 1];
			this->m_worker_num--;
			cout << "编号为" << del_id << "的员工信息已删除，剩余员工信息" << this->m_worker_num << "条" << endl;
			this->Save();
			system("pause");
			system("cls");
		}
		else {
			cout << endl <<"删除取消" << endl;
			system("pause");
			system("cls");
		}
	}
	else {
		cout << endl <<"无此编号的员工信息" << endl;
		system("pause");
		system("cls");
	}
}

void WorkerManager::ModEmp()
{
	if (0 == this->m_worker_num) {
		cout << "暂无员工信息" << endl;
		system("pause");
		system("cls");
		return;
	}
	enum Options
	{
		employee = 1,
		manager,
		boss
	};
	cout << "输入要修改的员工编号:>";
	int mod_id = -1;
	cin >> mod_id;
	int mod_set = 0;
	mod_set=this->IfIdExisted(mod_id, this->m_worker_arr, this->m_worker_num);
	if (-1 != mod_set) {//有这个员工
		int id = 0;
		string name = "0";
		int did = 0;
		while (1) {
			cout << "输入此员工的新编号:>";
			cin >> id;
			if (id < 0) {
				cout << "编号必须是非负整数" << endl;
				continue;
			}
			if ((-1 != IfIdExisted(id, this->m_worker_arr, this->m_worker_num))&&id!=mod_id) {//编号已有,且不是旧编号
				cout << endl << "此编号已被占据，换一个" << endl;
				continue;
			}
			else {//编号未被占据或者输入的编号未改变
				break;
			}
		}
		cout << "输入此员工的新名字:>";
		cin >> name;
		while (1) {
			cout << "选择此员工的新职位:";
			cout << "(1.职工  2.经理  3.老板)" << endl;
			cout << ":>";
			cin >> did;

			if (1 == did || 2 == did || 3 == did) {
				cout << "确认修改(y/n):>";
				char yn = 0;
				cin >> yn;
				if ('y' == yn) {
					delete this->m_worker_arr[mod_set];//释放内存
					switch (did) {
						case employee: {
							this->m_worker_arr[mod_set] = new Employee(id, name, 1);
							break;
						}
						case manager: {
							this->m_worker_arr[mod_set] = new Manager(id, name, 2);
							break;
						}
						case boss: {
							this->m_worker_arr[mod_set] = new Boss(id, name, 3);
							break;
						}
					}
					cout << "编号为" << mod_id << "的员工信息已修改" << endl;
					this->Save();
					system("pause");
					system("cls");
					return;
				}

				else {
					cout << "修改取消" << endl;
					system("pause");
					system("cls");
					return;
				}
				
			}

			else {
				cout << endl << "选择错误，重新选择" << endl;
				continue;
			}
		}
	}
	else {
		cout << endl << "无此编号的员工信息" << endl;
		system("pause");
		system("cls");
		return;
	}
	
}


void WorkerManager::Find()
{
	if (0 == this->m_worker_num) {
		cout << "暂无员工信息" << endl;
		system("pause");
		system("cls");
		return;
	}
	while (1) {
		cout << "1.按编号查找  2.按姓名查找"<<endl;
		cout << ":>";
		int select = 0;
		cin >> select;
		if (1 == select || 2 == select) {
			switch (select) {
			case 1:this->FindById();
				break;
			case 2:this->FindByName();
				break;
			}
			break;
		}
		else {
			cout << endl << "选择错误，重新选择"<<endl;
			continue;
		}
	}
}
void WorkerManager::FindById()
{
	cout << "输入要查找的员工编号:>";
	int find_id = -1;
	cin >> find_id;
	int find_set = 0;
	find_set = this->IfIdExisted(find_id, this->m_worker_arr, this->m_worker_num);
	if (-1 != find_set) {//有这个员工
		this->m_worker_arr[find_set]->ShowInfo();
	}
	else {//无此员工
		cout << "无此编号的员工信息" << endl;
	}
	system("pause");
	system("cls");
}
void WorkerManager::FindByName()
{
	cout << "输入要查找的员工姓名:>";
	string find_name = "0";
	cin >> find_name;
	bool name_exist_flag=0;
	for (int i = 0; i < this->m_worker_num; i++) {//同名的全打印
		if (find_name == this->m_worker_arr[i]->m_name) {
			this->m_worker_arr[i]->ShowInfo();
			name_exist_flag = 1;
		}
	}
	if(0==name_exist_flag) {//无此员工
		cout << "无此姓名的员工信息" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort()
{
	while (1) {
		cout << "按编号排序:(1.升序  2.降序):>";
		int s = 0;
		cin >> s;
		if (1 == s || 2 == s) {
			if (1 == s) {
				for (int i = 0; i < this->m_worker_num - 1; i++) {
					for (int j = 0; j < this->m_worker_num - 1 - i; j++) {
						Worker* tmp = NULL;
						if (this->m_worker_arr[j]->m_id > this->m_worker_arr[j + 1]->m_id) {
							tmp = this->m_worker_arr[j];
							this->m_worker_arr[j] = this->m_worker_arr[j + 1];
							this->m_worker_arr[j + 1] = tmp;
						}
					}
				}
			}
			else {
				for (int i = 0; i < this->m_worker_num - 1; i++) {
					for (int j = 0; j < this->m_worker_num - 1 - i; j++) {
						Worker* tmp = NULL;
						if (this->m_worker_arr[j]->m_id < this->m_worker_arr[j + 1]->m_id) {
							tmp = this->m_worker_arr[j];
							this->m_worker_arr[j] = this->m_worker_arr[j + 1];
							this->m_worker_arr[j + 1] = tmp;
						}
					}
				}
			}
			break;
		}
		else {
			cout<<endl << "选择错误，重新选择" << endl;
			continue;
		}
	}
	cout << "排序结果:" << endl;
	for (int i = 0; i < this->m_worker_num; i++) {
		this->m_worker_arr[i]->ShowInfo();
	}
	cout << "是否保存排序结果(y/n):>";
	char yn = 0;
	cin >> yn;
	if ('y' == yn) {
		this->Save();
	}
	else {
		cout << "排序结果未保存" << endl;
	}
	system("pause");
	system("cls");

}
int WorkerManager :: IfIdExisted(int id , Worker ** new_worker_arr , int temp_len)
{
	for (int i = 0; i < temp_len; i++) {//暂时有temp_len个无误的员工信息
		if (id == (**(new_worker_arr + i)).m_id) {//编号已存在，返回下标>=0，不存在返回-1
			return i;
		}
	}
	return -1;//此编号不存在，返回-1
}
void WorkerManager::Save()
{
	if (this->m_worker_arr!=NULL) {
		ofstream save_emp_file;
		save_emp_file.open(EMP_FILE, ios::out);
		for (int i = 0; i < this->m_worker_num; i++) {
			save_emp_file << ((this->m_worker_arr[i])->m_id) << " ";
			save_emp_file << ((this->m_worker_arr[i])->m_name) << " ";
			save_emp_file << ((this->m_worker_arr[i])->m_dept_id) << endl;
		}
		save_emp_file.close();
		cout << "文件已保存" << endl;
	}
}

void WorkerManager :: Print()
{
	if (0 == this->m_worker_num) {
		cout << "暂无员工信息" << endl;
		system("pause");
		system("cls");
		return;
	}//else

	for (int i = 0; i < this->m_worker_num; i++) {
		this->m_worker_arr[i]->ShowInfo();
	}
	system("pause");
	system("cls");
}
void WorkerManager::Clean()
{
	cout << "是否清空员工信息(y/n):>";
	char yn = 0;
	cin >> yn;
	if ('y' == yn) {
		for (int i = 0; i < this->m_worker_num; i++) {//释放内存
			delete this->m_worker_arr[i];
			this->m_worker_arr[i] = NULL;
		}
		delete this->m_worker_arr;
		this->m_worker_arr = NULL;
		this->m_worker_num = 0;
		this->m_empty_file_flag = 1;
		fstream clean;
		clean.open(EMP_FILE, ios::out|ios::trunc);//清空文件内容
		clean.close();
		cout << "文件已清空" << endl;
	}
	else {
		cout << "操作取消" << endl;
	}
	system("pause");
	system("cls");
}
void WorkerManager::Exit()
{
	
	cout << "已退出" << endl;
}