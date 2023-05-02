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
	int borrow_sort_num;		//대여순번 
	int sort_num;		//도서일련번호 
	int date[6];
	int rdate[6];	
}BORROW;


// 구조체 정의


#endif 
