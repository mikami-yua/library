#define _CRT_SECURE_NO_WARNINGS//vs�Գ�������˸Ľ�����Ҫ���к궨��
#include <stdio.h>
#include <stdlib.h>
//3.���ݵ����
//3.1 ��ʲô��������-----������/����-----������ѡ������
//3.2 ���ݵĽṹ-----��ͼ�����Ϣ
struct Node
{
	int data;
	struct Node* next;
};
//�б�ͷ������ͷ���������
//3.1.1������ͷ
struct Node* creatHead() {
	//��̬�ڴ�����
	struct Node* headNode = (struct Node*)malloc(sizeof(struct Node));
	//�����Ļ�������ʹ��ǰ�����ʼ��
	headNode->next = NULL;//��ͷ����Ҫ��ʼ��������
	return headNode;
}

//3.1.2�����ڵ㣨Ϊ������׼����  ���û������ݱ�Ϊ�ṹ�����
struct Node* createNode(int data) {
	struct Node* newNode= (struct Node*)malloc(sizeof(struct Node));
	//ֻ��������������Ĳ���
	newNode->data = data;
	newNode->next = NULL;
	return newNode;
}

//3.1.3 ��ӡ��ǰͷ�ڵ������
void printList(struct Node* head) {
	//��Ϊͷ�ڵ�û�����ݣ��ӵڶ����ڵ��ӡ����
	struct Node* p = head->next;
	while (p != NULL)
	{
		printf("%d\t", p->data);
		p = p->next;
	}
}

//3.1.4 ��������ֻ��Ҫһ�ֲ��뷽ʽ��ͷ�巨��
void insertNode(struct Node* head, int data) {
	//1.��������ڵ�
	struct Node* newNode = createNode(data);
	//2.ͷ��
	newNode->next = head->next;
	head->next = newNode;
}

//3.1.5 ָ��λ��ɾ��(ͨ��������ɾ��)
void deleteNode(struct Node* head, int data) {
	struct Node* posLeftNode = head;
	struct Node* posNode = head->next;
	while (posNode!=NULL && posNode->data!=data)
	{
		posLeftNode = posNode;
		posNode = posNode->next;
	}
	//���۲��ҵĽ��
	if (posNode == NULL) {
		printf("δ�ҵ�\n");
		return;
	}
	else
	{
		posLeftNode->next = posNode->next;
		free(posNode);
		posNode = NULL;
	}

}


//1.д����---���˵�---��ģ��
void makeMenu() {
	printf("----------------------------------\n");
	printf("   xxooͼ�����ϵͳ\n");
	printf("\t0.�˳�ϵͳ\n");
	printf("\t1.�Ǽ��鼮\n");
	printf("\t2.����鼮\n");
	printf("\t3.�����鼮\n");
	printf("\t4.�黹�鼮\n");
	printf("\t5.�鼮����\n");
	printf("\t6.ɾ���鼮\n");
	printf("\t7.�����鼮\n");
	printf("----------------------------------\n");
	printf("������0~7��");
}

//2.������
void keyDown() {
	int userKey = 0;
	scanf("%d",&userKey);//ע����Ҫȡ��ַ
	switch (userKey)
	{
	case 0:
		printf("���˳� ��\n");
		printf("�˳��ɹ�\n");
		system("pause");
		exit(0);
		break;
	case 1:
		printf("���Ǽ� ��\n");
		break;
	case 2:
		printf("����� ��\n");
		break;
	case 3:
		printf("������ ��\n");
		break;
	case 4:
		printf("���黹 ��\n");
		break;
	case 5:
		printf("������ ��\n");
		break;
	case 6:
		printf("��ɾ�� ��\n");
		break;
	case 7:
		printf("������ ��\n");
		break;
	default:
		printf("��error ��\n");
		break;
	}
}

int main() {
	/*
	//1.ָ����α�ɱ���
	int* p = NULL;
	int a = 1;
	//1.1 �ñ�����ַ
	p = &a;//*p����һ������
	printf("%d\n", *p);//*p=1  p=9435692
	//1.2 ��̬�ڴ�����
	p = (int*)malloc(sizeof(int));
	*p = 1003;
	printf("%d\n", *p);//1003

	//2.�ṹ��
	struct data C;
	//2.1ͨ��ָ����ʽṹ�������ָ��ָ��
	struct data* pD = &C;
	pD->A = 1002;
	//2.2ͨ�������ķ�ʽ���ʣ�����.��Ա��
	C.A = 1001;

	//3.��������ṹ�������
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