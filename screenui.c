#include "common.h"
#include "client.h"
#include "book.h"
#include "borrow.h"
#include "admin.h"
#include "fileio.h"
#include "screenui.h"




int mainmenu(){
	int cho;
	printf(">> ������ ���� << \n");
	printf("1.ȸ������	2.�α��� 3.���α׷� ����\n");
	printf("��ȣ�� �����ϼ���:");
	scanf("%d",&cho); 
	return cho;
}
int adminmenu(){
	int cho;
	printf(">> ������ �޴� <<\n");
	printf("1. ���� ���\n");
	printf("2.���� ����\n");
	printf("3.���� �뿩\n");
	printf("4.���� �ݳ�\n");
	printf("5.���� �˻�\n");
	printf("6.ȸ�����\n");
	printf("7.�뿩��Ϻ���\n");
	printf("8.�α׾ƿ�\n");
	printf("9.���α׷� ����\n"); 
	printf("��ȣ�� �����ϼ���:"); 
	scanf("%d",&cho);
	return cho;
}
int clientsubmenu(){
	int cho;
	printf("1.�̸� �˻�\n");
	printf("2.�й� �˻�\n");
	printf("3.��ü �˻�\n");
	printf("��ȣ�� �����ϼ���:"); 
	scanf("%d",&cho);
	return cho;
}
int clientmenu(){
	int cho;
	printf(">> ȸ�� �޴� << \n");
	printf("1.���� �˻�\n");
	printf("2.�뿩 ���\n");
	printf("3.������������\n");
	printf("4.ȸ��Ż��\n");
	printf("5.�α׾ƿ�\n");
	printf("6.���α׷� ����\n");
	printf("��ȣ�� �����ϼ���:"); 
	scanf("%d",&cho);
	return cho;
}
int booksearchmenu(){
	int cho;
	printf(">> ���� �˻� <<\n");
	printf("1. ������ �˻�\n");
	printf("2.���ǻ�� �˻�\n");
	printf("3.ISBN �˻�\n");
	printf("4.���ڸ� �˻�\n");
	printf("5.��ü �˻�\n");
	printf("6.������\n");
	printf("��ȣ�� �����ϼ���:"); 
	scanf("%d",&cho);
	return cho;
}
	 

