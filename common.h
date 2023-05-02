#ifndef _COMMON_ 
#define _COMMON_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
	char student_num[10];
	char password[10];
	char name[10];
	char addr[30];
	char phone_num[20];
}CLIENT;

typedef struct {
	char book_name[20];
	char maker[20];
	char author[20];
	char ISBN[20];
	char place[20];
	int  yn;						 
	int sort_num;
}BOOK;

typedef struct {
	char student_num[10];
	int borrow_sort_num;		//�뿩���� 
	int sort_num;		//�����Ϸù�ȣ 
	int date[6];
	int rdate[6];	
}BORROW;


// ����ü ����


#endif 
