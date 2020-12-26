#define _CRT_SECURE_NO_WARNINGS//vs对程序进行了改进，需要进行宏定义
#include <stdio.h>
#include <stdlib.h>
//3.数据的设计
//3.1 用什么处理数据-----》数组/链表-----》容器选择链表
//3.2 数据的结构-----》图书的信息
struct Node
{
	int data;
	struct Node* next;
};
//有表头链表，表头不存放数据
//3.1.1创建表头
struct Node* creatHead() {
	//动态内存申请
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	//变量的基本规则：使用前必须初始化
	headNode->next = NULL;//表头不需要初始换数据域
	return headNode;
}

//3.1.2创建节点（为插入做准备）  把用户的数据变为结构体变量
struct Node* createNode(int data) {
	struct Node* newNode= (struct Node*)malloc(sizeof(struct Node));
	//只是增加了数据域的操作
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

//3.1.3 打印当前头节点的链表
void printList(struct Node* head) {
	//因为头节点没有数据，从第二个节点打印数据
	struct Node* p = head->next;
	while (p != NULL)
	{
		printf("%d\t", p->data);
		p = p->next;
	}
}

//3.1.4 插入链表，只需要一种插入方式（头插法）
void insertNode(struct Node* head, int data) {
	//1.创建插入节点
	struct Node* newNode = createNode(data);
	//2.头插
	newNode->next = head->next;
	head->next = newNode;
}

//3.1.5 指定位置删除(通过数据做删除)
void deleteNode(struct Node* head, int data) {
	struct Node* posLeftNode = head;
	struct Node* posNode = head->next;
	while (posNode!=NULL && posNode->data!=data)
	{
		posLeftNode = posNode;
		posNode = posNode->next;
	}
	//讨论查找的结果
	if (posNode == NULL) {
		printf("未找到\n");
		return;
	}
	else
	{
		posLeftNode->next = posNode->next;
		free(posNode);
		posNode = NULL;
	}

}


//1.写界面---》菜单---》模块
void makeMenu() {
	printf("----------------------------------\n");
	printf("   xxoo图书管理系统\n");
	printf("\t0.退出系统\n");
	printf("\t1.登记书籍\n");
	printf("\t2.浏览书籍\n");
	printf("\t3.借阅书籍\n");
	printf("\t4.归还书籍\n");
	printf("\t5.书籍排序\n");
	printf("\t6.删除书籍\n");
	printf("\t7.查找书籍\n");
	printf("----------------------------------\n");
	printf("请输入0~7：");
}

//2.做交互
void keyDown() {
	int userKey = 0;
	scanf("%d",&userKey);//注意需要取地址
	switch (userKey)
	{
	case 0:
		printf("【退出 】\n");
		printf("退出成功\n");
		system("pause");
		exit(0);
		break;
	case 1:
		printf("【登记 】\n");
		break;
	case 2:
		printf("【浏览 】\n");
		break;
	case 3:
		printf("【借阅 】\n");
		break;
	case 4:
		printf("【归还 】\n");
		break;
	case 5:
		printf("【排序 】\n");
		break;
	case 6:
		printf("【删除 】\n");
		break;
	case 7:
		printf("【查找 】\n");
		break;
	default:
		printf("【error 】\n");
		break;
	}
}

int main() {
	/*
	//1.指针如何变成变量
	int* p = NULL;
	int a = 1;
	//1.1 用变量地址
	p = &a;//*p就是一个变量
	printf("%d\n", *p);//*p=1  p=9435692
	//1.2 动态内存申请
	p = (int*)malloc(sizeof(int));
	*p = 1003;
	printf("%d\n", *p);//1003

	//2.结构体
	struct data C;
	//2.1通过指针访问结构体变量（指针指向）
	struct data* pD = &C;
	pD->A = 1002;
	//2.2通过变量的方式访问（变量.成员）
	C.A = 1001;

	//3.链表（多个结构体变量）
	*/

	struct Node* list = creatHead();
	for (int i = 0; i < 3; i++)
	{
		insertNode(list, i);
	}
	deleteNode(list, 0);
	printList(list);



	while (1)
	{
		makeMenu();
		keyDown();
		system("pause");
		system("cls");
	}

	printf("Hello World\n");
	system("pause");
	return 0;
}