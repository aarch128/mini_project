#define _CRT_SECURE_NO_WARNINGS
#include"WorkerManager.h"
using namespace std;
WorkerManager::WorkerManager()
{
	ifstream init_emp_file;
	init_emp_file.open(EMP_FILE, ios::in);

	if (0 == init_emp_file.is_open()) {//�ļ�������
		//cout << "empfile is unexisted"<<endl;
		this->m_empty_file_flag = 1;
		this->m_worker_num = 0;
		this->m_worker_arr = NULL;

		init_emp_file.close();
		return;
	}
	char eof_flag = '1';
	init_emp_file >> eof_flag;
	if (1 == init_emp_file.eof()) {//�ļ����ڵ�������
		//cout << "empfile is emptied" << endl;
		this->m_empty_file_flag = 1;
		this->m_worker_num = 0;
		this->m_worker_arr = NULL;
		init_emp_file.close();
		return;
	}
	else {//�ļ��������ݲ�Ϊ��
		init_emp_file.close();//�ر�̽���ļ��Ƿ�򿪶��򿪵��ļ�
		int get_file_emp_num = 0;
		this->m_empty_file_flag = 0;
		get_file_emp_num = GetEmpNum();//��ȡ�ļ�������
		this->m_worker_num = get_file_emp_num;
		this->m_worker_arr = NULL;
		this->InitEmp();//��ȡ���ڴ�
		
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
int WorkerManager::GetEmpNum()//��ȡ�ļ�����Ϣ�������ļ��������
{
	ifstream get_emp_num;
	get_emp_num.open(EMP_FILE, ios::in);
	int num = 0;
	char temp[1024] = {'0'};
	while(get_emp_num.getline(temp,sizeof(temp))){//ÿ�ζ�ȡһ�У�����EOFֵΪ0
		num++;
	}
	get_emp_num.close();
	return num;
}
void WorkerManager::InitEmp()//�ļ��������
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
		init_emp>>tmp;//��ȡid
		id = atoi(tmp);//����id
		memset(tmp, 0, 128);
		init_emp >> name;//����name
		init_emp >> tmp;//��ȡdid
		did = atoi(tmp);//����did
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
	cout << "**\tְ������ϵͳ        **" << endl;
	cout << "*\t  0.�˳�ϵͳ         *" << endl;
	cout << "*\t1.����ְ����Ϣ       *" << endl;
	cout << "*\t2.��ʾְ����Ϣ       *" << endl;
	cout << "*\t3.ɾ����ְְ��       *" << endl;
	cout << "*\t4.�޸�ְ����Ϣ       *" << endl;
	cout << "*\t5.����ְ����Ϣ       *" << endl;
	cout << "*\t6.���ձ������       *" << endl;
	cout << "*\t7.��������ĵ�       *" << endl;
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
	cout << "�������Ӹ���:>";
	int add_num = 0;
	cin >> add_num;
	if (add_num > 0) {
		int new_worker_num = this->m_worker_num + add_num;//��Ա������
		Worker** new_worker_arr = new Worker * [new_worker_num];//worker*��������ڶ���

		if (this->m_worker_arr != NULL) {//�ɵ�worker*����������ά�����Ƚ���Ա������ʱ����ά��
			for (int i = 0; i < this->m_worker_num; i++) {
				new_worker_arr[i] = this->m_worker_arr[i];//���ɵ�ά��ָ�븴�Ƶ�new_worker_arr[i]
			}
		}//else�ɵ�worker*����Ϊ��
		for (int j = 0; j < add_num; j++) {
			int id = 0;
			string name ="0";
			int did = 0;
			while (1) {
				cout << "�����(" << j + 1 <<"/"<<add_num << ")��������Ա�ı��:>";
				cin >> id;
				if (id < 0) {
					cout << "��ű����ǷǸ�����" << endl;
					continue;
				}
				if (-1 != IfIdExisted(id, new_worker_arr, this->m_worker_num + j)) {
					cout <<endl<< "�˱���ѱ�ռ�ݣ���һ��" << endl;
				}
				else {//���δ��ռ��
					break;
				}
			}
			cout << "�����(" << j + 1 << "/" << add_num << ")��������Ա������:>";
			cin >> name;
			while (1) {
				cout << "ѡ���(" << j + 1 << "/" << add_num << ")��Ա����ְλ:";
				cout << "(1.ְ��  2.����  3.�ϰ�)" << endl;
				cout << ":>";
				cin >> did;
				
				if (1 == did || 2 == did || 3 == did) {
					switch (did) {
						case employee: {//�����еĺ��濪ʼ����
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
					break;//����while
				}
				else {
					cout << endl<<"ѡ���������ѡ��" << endl;
				}
			}
		}//�������
		if (this->m_worker_arr != NULL) {//�����ͷž��ڴ棬���ÿվ�ָzhen
			this->m_worker_arr = NULL;
		}
		this->m_worker_arr = new_worker_arr;//������ʱָ������
		this->m_worker_num = new_worker_num;//�̳�������
		new_worker_arr=NULL;//��ʱworker*�����ÿ�
	}
	else if (0 == add_num) {
		cout << "����δ����" << endl;
	}
	else {
		cout << "�������" << endl;
	}
	cout << "�ɹ����" << add_num << "��Ա����Ϣ��" << "�ֹ���" << this->m_worker_num << "��Ա����Ϣ" << endl;
	this->Save();
	this->m_empty_file_flag = 0;//����֮���ļ�Ϊ�ձ�־λ��0
	system("pause");
	system("cls");
}
void WorkerManager::DelEmp()
{
	if (0 == this->m_worker_num) {
		cout << "����Ա����Ϣ" << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "����Ҫɾ��Ա����Ϣ�ı��:>";
	int del_id = -1;
	cin >> del_id;
	int ret_set = -1;
	ret_set=this->IfIdExisted(del_id, this->m_worker_arr, this->m_worker_num);
	if (-1 != ret_set) {//��Ŵ���
		cout << "ȷ��ɾ��(y/n):>";
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
			cout << "���Ϊ" << del_id << "��Ա����Ϣ��ɾ����ʣ��Ա����Ϣ" << this->m_worker_num << "��" << endl;
			this->Save();
			system("pause");
			system("cls");
		}
		else {
			cout << endl <<"ɾ��ȡ��" << endl;
			system("pause");
			system("cls");
		}
	}
	else {
		cout << endl <<"�޴˱�ŵ�Ա����Ϣ" << endl;
		system("pause");
		system("cls");
	}
}

void WorkerManager::ModEmp()
{
	if (0 == this->m_worker_num) {
		cout << "����Ա����Ϣ" << endl;
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
	cout << "����Ҫ�޸ĵ�Ա�����:>";
	int mod_id = -1;
	cin >> mod_id;
	int mod_set = 0;
	mod_set=this->IfIdExisted(mod_id, this->m_worker_arr, this->m_worker_num);
	if (-1 != mod_set) {//�����Ա��
		int id = 0;
		string name = "0";
		int did = 0;
		while (1) {
			cout << "�����Ա�����±��:>";
			cin >> id;
			if (id < 0) {
				cout << "��ű����ǷǸ�����" << endl;
				continue;
			}
			if ((-1 != IfIdExisted(id, this->m_worker_arr, this->m_worker_num))&&id!=mod_id) {//�������,�Ҳ��Ǿɱ��
				cout << endl << "�˱���ѱ�ռ�ݣ���һ��" << endl;
				continue;
			}
			else {//���δ��ռ�ݻ�������ı��δ�ı�
				break;
			}
		}
		cout << "�����Ա����������:>";
		cin >> name;
		while (1) {
			cout << "ѡ���Ա������ְλ:";
			cout << "(1.ְ��  2.����  3.�ϰ�)" << endl;
			cout << ":>";
			cin >> did;

			if (1 == did || 2 == did || 3 == did) {
				cout << "ȷ���޸�(y/n):>";
				char yn = 0;
				cin >> yn;
				if ('y' == yn) {
					delete this->m_worker_arr[mod_set];//�ͷ��ڴ�
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
					cout << "���Ϊ" << mod_id << "��Ա����Ϣ���޸�" << endl;
					this->Save();
					system("pause");
					system("cls");
					return;
				}

				else {
					cout << "�޸�ȡ��" << endl;
					system("pause");
					system("cls");
					return;
				}
				
			}

			else {
				cout << endl << "ѡ���������ѡ��" << endl;
				continue;
			}
		}
	}
	else {
		cout << endl << "�޴˱�ŵ�Ա����Ϣ" << endl;
		system("pause");
		system("cls");
		return;
	}
	
}


void WorkerManager::Find()
{
	if (0 == this->m_worker_num) {
		cout << "����Ա����Ϣ" << endl;
		system("pause");
		system("cls");
		return;
	}
	while (1) {
		cout << "1.����Ų���  2.����������"<<endl;
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
			cout << endl << "ѡ���������ѡ��"<<endl;
			continue;
		}
	}
}
void WorkerManager::FindById()
{
	cout << "����Ҫ���ҵ�Ա�����:>";
	int find_id = -1;
	cin >> find_id;
	int find_set = 0;
	find_set = this->IfIdExisted(find_id, this->m_worker_arr, this->m_worker_num);
	if (-1 != find_set) {//�����Ա��
		this->m_worker_arr[find_set]->ShowInfo();
	}
	else {//�޴�Ա��
		cout << "�޴˱�ŵ�Ա����Ϣ" << endl;
	}
	system("pause");
	system("cls");
}
void WorkerManager::FindByName()
{
	cout << "����Ҫ���ҵ�Ա������:>";
	string find_name = "0";
	cin >> find_name;
	bool name_exist_flag=0;
	for (int i = 0; i < this->m_worker_num; i++) {//ͬ����ȫ��ӡ
		if (find_name == this->m_worker_arr[i]->m_name) {
			this->m_worker_arr[i]->ShowInfo();
			name_exist_flag = 1;
		}
	}
	if(0==name_exist_flag) {//�޴�Ա��
		cout << "�޴�������Ա����Ϣ" << endl;
	}
	system("pause");
	system("cls");
}

void WorkerManager::Sort()
{
	while (1) {
		cout << "���������:(1.����  2.����):>";
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
			cout<<endl << "ѡ���������ѡ��" << endl;
			continue;
		}
	}
	cout << "������:" << endl;
	for (int i = 0; i < this->m_worker_num; i++) {
		this->m_worker_arr[i]->ShowInfo();
	}
	cout << "�Ƿ񱣴�������(y/n):>";
	char yn = 0;
	cin >> yn;
	if ('y' == yn) {
		this->Save();
	}
	else {
		cout << "������δ����" << endl;
	}
	system("pause");
	system("cls");

}
int WorkerManager :: IfIdExisted(int id , Worker ** new_worker_arr , int temp_len)
{
	for (int i = 0; i < temp_len; i++) {//��ʱ��temp_len�������Ա����Ϣ
		if (id == (**(new_worker_arr + i)).m_id) {//����Ѵ��ڣ������±�>=0�������ڷ���-1
			return i;
		}
	}
	return -1;//�˱�Ų����ڣ�����-1
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
		cout << "�ļ��ѱ���" << endl;
	}
}

void WorkerManager :: Print()
{
	if (0 == this->m_worker_num) {
		cout << "����Ա����Ϣ" << endl;
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
	cout << "�Ƿ����Ա����Ϣ(y/n):>";
	char yn = 0;
	cin >> yn;
	if ('y' == yn) {
		for (int i = 0; i < this->m_worker_num; i++) {//�ͷ��ڴ�
			delete this->m_worker_arr[i];
			this->m_worker_arr[i] = NULL;
		}
		delete this->m_worker_arr;
		this->m_worker_arr = NULL;
		this->m_worker_num = 0;
		this->m_empty_file_flag = 1;
		fstream clean;
		clean.open(EMP_FILE, ios::out|ios::trunc);//����ļ�����
		clean.close();
		cout << "�ļ������" << endl;
	}
	else {
		cout << "����ȡ��" << endl;
	}
	system("pause");
	system("cls");
}
void WorkerManager::Exit()
{
	
	cout << "���˳�" << endl;
}