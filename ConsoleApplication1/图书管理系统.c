#define _CRT_SECURE_NO_WARNINGS//vs对程序进行了改进，需要进行宏定义
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//3.数据的设计
//3.1 用什么处理数据-----》数组/链表-----》容器选择链表
//3.2 数据的结构-----》图书的信息
struct BookInfo {
	char name[20];//书名
	float price;//价格
	int num;//数量
};

struct Node
{
	struct BookInfo data;
	struct Node* next;
};
struct Node* list = NULL;


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
struct Node* createNode(struct BookInfo data) {
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
	printf("name\tprice\tnum\n");
	while (p != NULL)
	{
		printf("%s\t%0.1f\t%d\n",p->data.name,p->data.price,p->data.num);
		p = p->next;
	}
}

//3.1.4 插入链表，只需要一种插入方式（头插法）
void insertNode(struct Node* head, struct BookInfo data) {
	//1.创建插入节点
	struct Node* newNode = createNode(data);
	//2.头插
	newNode->next = head->next;
	head->next = newNode;
}

//3.1.5 指定位置删除(通过数据做删除)
void deleteNodeByName(struct Node* head, char *bookName) {
	struct Node* posLeftNode = head;
	struct Node* posNode = head->next;
	//书籍名字是字符串，使用字符串比较函数处理
	while (posNode!=NULL && strcmp(bookName,posNode->data.name))//strcmp相同返回0
	{
		posLeftNode = posNode;
		posNode = posNode->next;
	}
	//讨论查找的结果
	if (posNode == NULL) {
		printf("cannot find\n");
		return;
	}
	else
	{	
		printf("delect successful!\n");
		posLeftNode->next = posNode->next;
		free(posNode);
		posNode = NULL;
	}

}

//链表的查找
struct Node* searchByName(struct Node* head,char* bookname) {
	struct Node* pos = head->next;
	while (pos !=NULL && strcmp(pos->data.name,bookname))
	{
		pos = pos->next;
	}
	return pos;
}

//1.写界面---》菜单---》模块
void makeMenu() {
	printf("----------------------------------\n");
	printf("   xxoo book manage system\n");
	printf("\t0.exit system\n");
	printf("\t1.update book\n");
	printf("\t2.lookthough books\n");
	printf("\t3.carry books\n");
	printf("\t4.return books\n");
	printf("\t5.sort books\n");
	printf("\t6.delete books\n");
	printf("\t7.find books\n");
	printf("----------------------------------\n");
	printf("please input 0~7:");
}
//文件存操作
void saveInfoToFile(const char *filename,struct Node* head) {
	//打开文件
	FILE* fp = fopen(filename, "w");//用写的方式打开文件
	struct Node* p = head->next;
	while (p!=NULL)
	{
		fprintf(fp, "%s\t%0.1f\t%d\n", p->data.name, p->data.price, p->data.num);//向文件中打印
		p = p->next;
	}
	fclose(fp);
}

//文件读操作
void readInfoFromFile(const char* filename, struct Node* head) {
	FILE* fp = fopen(filename, "r");//用读的方式打开文件
	//开始的时候是不存在配置文件的
	if (fp==NULL)
	{//不存在把文件创建
		fp = fopen(filename, "w+");//使用具有创建功能的方式打开文件
	}
	//把文件当作临时键盘
	struct BookInfo temp;
	while (fscanf(fp,"%s\t%f\t%d\n",temp.name,&temp.price,&temp.num)!=EOF)//不等于文件结束标志时做插入
	{
		insertNode(head,temp);
	}

	fclose(fp);
}
//排序
void bubbleSortList(struct Node* head) {
	for (struct Node* p = head->next; p != NULL; p=p->next)
	{
		for (struct Node* q=head->next;q->next!=NULL;q=q->next)
		{
			if (q->data.price > q->next->data.price) {
				//交换data部分
				struct BookInfo temp = q->data;
				q->data = q->next->data;
				q->next->data = temp;
			}
		}
	}
	printList(head);
}


//2.做交互
void keyDown() {
	int userKey = 0;
	struct BookInfo tempBook;
	struct Node* result = NULL;
	scanf("%d",&userKey);//注意需要取地址
	switch (userKey)
	{
	case 0:
		printf("exit\n");
		printf("exit seccuss!\n");
		system("pause");
		exit(0);
		break;
	case 1:
		printf("update\n");
		printf("please input book info [name,price,num] :");
		scanf("%s%f%d",tempBook.name,&tempBook.price,&tempBook.num);//字符串不需要取地址
		insertNode(list,tempBook);
		saveInfoToFile("bookinfo.txt", list);
		break;
	case 2:
		printf("lookthough\n");
		printList(list);
		break;
	case 3:
		printf("carry\n");//书籍存在可以借阅，num-1
		printf("please input bookname that you want to carryout: \n");
		scanf("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			printf("you cannot carry the book that we do not have \n");
		}else{
			if (result->data.num > 0) {
				result->data.num--;
				printf("carry out successful!\n");
			}
			else {
				printf("sorry! all of this book have been carried out \n");
			}
		}
		break;
	case 4:
		printf("return\n");//当前书籍num+1
		printf("please input bookname that you want to return: \n");
		scanf("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			printf("this book is not belong to our library! \n");
		}
		else {
			result->data.num++;
			printf("thanks for your return back! \n");
		}
		break;
	case 5:
		printf("sort\n");
		bubbleSortList(list);
		break;
	case 6:
		printf("delete\n");
		printf("please input the bookname that you want to delete: ");
		scanf("%s", tempBook.name);
		deleteNodeByName(list, tempBook.name);
		//数据的修改同步到文件
		saveInfoToFile("bookinfo.txt", list);
		break;
	case 7:
		printf("find\n");
		printf("please input the bookname that you want to find: ");
		scanf("%s", tempBook.name);
		result = searchByName(list, tempBook.name);
		if (result == NULL) {
			printf("cannot find this book\n");
		}
		else
		{	
			printf("name\tprice\tnum\n");
			printf("%s\t%0.1f\t%d\n", result->data.name, result->data.price, result->data.num);
		}
		break;
	default:
		printf("error\n");
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

	/*
	
	for (int i = 0; i < 3; i++)
	{
		insertNode(list, i);
	}
	deleteNode(list, 0);
	printList(list);
	*/

	list = creatHead();
	readInfoFromFile("bookinfo.txt", list);
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