#define _CRT_SECURE_NO_WARNINGS
#include "WorkerManager.h"
using namespace std;
void Test()
{
	Worker* w1 = new Boss(1, "张三", 1);
	w1->ShowInfo();
	delete w1;
	w1 = new Manager(1, "张三", 1);
	w1->ShowInfo();
	delete w1;
	w1 = new Employee(1, "张三", 1);
	w1->ShowInfo();
	delete w1;
}
int main()
{
	enum Options
	{
		exit = 0,
		add,
		print,
		del,
		modify,
		search,
		sort,
		clean
	};
	WorkerManager w_m1;

	int choice = 1;

	while (choice) {
		w_m1.ShowMenu();
		//Test();
		cout << "输入选项号码:>";
		cin >> choice;
		switch (choice) {
			case exit: {
				w_m1.Exit();
				break;
			}
			case add: {
				w_m1.AddWorker();
				break;
			}
			case print: {
				//system("cls");
				//w_m1.ShowMenu();
				w_m1.Print();
				break;
			}
			case del: {
				w_m1.DelEmp();
				break;
			}	
			case modify: {
				w_m1.ModEmp();
				break;
			}
			case search: {
				w_m1.Find();
				break;
			}
			case sort: {
				w_m1.Sort();
				break;
			}
			case clean: {
				w_m1.Clean();
				break;
			}
			default: {
				system("cls");
		
				break;
			}
		}

	}
	return 0;
}