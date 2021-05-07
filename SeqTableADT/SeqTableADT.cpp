// SeqTableADT.cpp : Defines the entry point for the application.
// This source code file conatains main entry of the ADT test program

#include "SeqTableADT.h"

#define PRINT_STATUS	printStatus(st, op);
#define t_sleep(x)		std::this_thread::sleep_for(std::chrono::milliseconds((x)));

using namespace std;

int multiSeqMode = 0; // if you selected multiSeq, this value will turn into 1

// Main Entry of ADT Test Program
int main(int argc, char* argv[])
{
	system("cls"); // clear screen
	printMenu();
	// Initialization of variables
	int			op = 1;
	status		st = OK;
	SqList		L1;
	SqList&		L = L1;
	LISTS		Ls;
	ElemType	e;
	ElemType	pre;
	int			i;
	char		fileName[1000];
	char		listName[1000];
	memset(&L1, 0, sizeof(L1));
	memset(&Ls, 0, sizeof(Ls));
	memset(fileName, 0, sizeof(fileName));
	memset(listName, 0, sizeof(listName));

	// main choices choosing loop
	while (op) {
		if (multiSeqMode == 0) L = L1;
		cout << "\n您的选项：";
		cin >> op;
		switch (op)
		{
		case 0:
			puts("谢谢使用。我去玩咯~");
			t_sleep(1500);
			// 这是附加功能 (> = <)
			return 0;
		case 1:
			st = InitList(L);
			PRINT_STATUS;
			break;
		case 2:
			st = DestroyList(L);
			PRINT_STATUS;
			break;
		case 3:
			st = ClearList(L);
			PRINT_STATUS;
			break;
		case 4:
			st = ListEmpty(L);
			if (st == INFEASIBLE) {
				puts("线性表不存在！");
			}
			else {
				if (st)puts("线性表是空的。");
				else puts("线性表非空。");
			}
			break;
		case 5:
			st = ListLength(L);
			if (st==INFEASIBLE)puts("线性表不存在！");
			else printf("线性表的长度是：%d\n", st);
			t_sleep(500);
			break;
		case 6:
			puts("获取线性表的第i个元素，请输入i:");
			cin >> i;
			st = GetElem(L, i, e);
			PRINT_STATUS;
			if (st == OK) {
				cout << "第 " << i << "个元素是 " << e << endl;
				t_sleep(500);
			}
			break;
		case 7:
			puts("查找元素e，请输入您要查找的元素：");
			cin >> e;
			st = LocateElem(L, e);
			PRINT_STATUS;
			if (st == OK){
				cout << "您要查找的元素的位置是" << st << endl;
				t_sleep(500);
			}
			break;
		case 8:
			puts("您正在查找e的前驱，现在请输入e");
			cin >> e;
			st = PriorElem(L, e, pre);
			PRINT_STATUS;
			if (st == OK) {
				cout << e << "的前驱是" << pre << endl;
				t_sleep(500);
			}
			break;
		case 9:
			puts("您正在查找e的后继，现在请输入e");
			cin >> e;
			st = NextElem(L, e, pre);
			PRINT_STATUS;
			if (st == OK) {
				cout << e << "的后继是" << pre << endl;
				t_sleep(500);
			}
			break;
		case 10:
			puts("您正在尝试将e插入到表中第i个元素之前");
			printf("现在请您输入e:");
			cin >> e;
			printf("\n现在请您输入i:");
			cin >> i;
			st = ListInsert(L, i, e);
			PRINT_STATUS;
			break;
		case 11:
			puts("您正在尝试删除表中第i个元素。");
			printf("现在，请您输入i:");
			cin >> i;
			st = ListDelete(L, i, e);
			PRINT_STATUS;
			if (st == OK) {
				cout << "您删除了" << e << endl;
				t_sleep(500);
			}
			break;
		case 12:
			st = ListTraverse(L);
			PRINT_STATUS;
			break;
		case 13:
			puts("输入文件名：");
			cin >> fileName;
			st = SaveList(L, fileName);
			PRINT_STATUS;
			break;
		case 14:
			puts("输入文件名：");
			cin >> fileName;
			st = LoadList(L, fileName);
			PRINT_STATUS;
			break;
		// Multi-Seq Table Management Start.
		case 15:
			puts("您即将在列表组中添加一个列表，请输入她的名字：");
			cin >> listName;
			st = AddList(Ls, listName);
			PRINT_STATUS;
			break;
		case 16:
			puts("输入要删除的线性表：");
			cin >> listName;
			st = RemoveList(Ls, listName);
			PRINT_STATUS;
			break;
		case 17:
			puts("输入要查找的线性表：");
			cin >> listName;
			st = LocateList(Ls, listName);
			PRINT_STATUS;
			if (st != ERROR) {
				cout << listName << " 的位置在 " << st;
				t_sleep(500);
			}
			break;
		default:
			// puts("您惊扰了 Witch");
			puts("您输入了一个不太合理的数字哦~");
			puts("请重新输入");
			break;
		}
		t_sleep(500);
		printMenu();
	}
	return 0;
}


void printStatus(int st, int op) {
	/// <summary>
	/// 状态码处理和打印函数
	/// </summary>
	/// <param name="st">状态码</param>
	/// <param name="op">在目录中的选项</param>
	if (st == INFEASIBLE) {
		switch (op) {
		case 1:case 14:
			puts("线性表已经存在！");
			break;
		default:
			puts("线性表不存在！");
		}
		return;
	}
	else if (st == OK) {
		puts("[OK]\t操作成功！");
		return;
	}
	else if (st == ERROR) {
		switch (op) {
		case 1:
			puts("[ERROR]\t分配内存错误！");
			break;
		case 6:
			puts("[ERROR]\t输入的i不合法！");
			break;
		case 7:
			puts("查找的元素不存在！");
			break;
		case 8:
			puts("查找的元素没有前驱或者元素不合法！");
			break;
		case 10:
			puts("插入的位置不合法，或者内存分配错误！");
			break;
		case 11:
			puts("要删除的位置不合法！");
			break;
		case 15:
			puts("输入的名字已经存在一个线性表！");
			break;
		case 16:case 17:
			puts("该名字的线性表不存在！");
			break;
		default:
			puts("[ERROR]\t[UNEXPECTED]\t未经处理的异常！");
			break;
		}
		return;
	}
	else if (st == FILEERROR) {
		puts("文件打开失败！");
		return;
	}

}


void printMenu() {
	puts("\n     欢迎使用这个系统。");
	puts("     来自高盟凯的问候。");
	puts("==================================");
	puts("     输入数字来进行活动");
	puts("==================================");
	puts("0.   退了");
	puts("1.   初始化一个线性表");
	puts("2.   销毁一个线性表");
	puts("3.   清空一个线性表");
	puts("4.   线性表是空的吗？");
	puts("5.   求线性表的长度");
	puts("6.   获取指定位置的元素");
	puts("7.   查找某个指定的元素返回位置");
	puts("8.   某元素的前驱");
	puts("9.   某元素的后继");
	puts("10.  在第i位置前边插入元素");
	puts("11.  删除某个位置的元素并保存");
	puts("12.  打印线性表的每个元素");
	puts("13.  保存线性表到文件");
	puts("14.  从文件加载表");
	puts("15. 【多线性表管理】插入一个空的线性表");
	puts("16. 【多线性表管理】删除一个线性表");
	puts("17. 【多线性表管理】查找一个线性表的逻辑位置");
	//puts("20. 【附加功能】");
}