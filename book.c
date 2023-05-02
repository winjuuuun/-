#include "common.h"
#include "client.h"
#include "book.h"
#include "borrow.h"
#include "admin.h"
#include "fileio.h"
#include "screenui.h"
extern CLIENT **g_client;
extern BOOK **g_book;
extern BORROW **g_borrow;
extern int numofclient;
extern int numofbook;
extern int numofborrow;

//�������� �뿩�� ���� �Ϸù�ȣ�� �ٲ��� �Ǵ� ���� �ٲ���Ѵٸ� �뿩����� ������ȣ�� ���� �ٲٱ� -> �������� ������ȣ �ٲٱ� 
//==>�߰��� å�� ISBN�� �뿩�� å���� ISBN���� ũ�ٸ� �뿩�� å�� ������ȣ�� �� �ٲ�� �ݴ��� ��츸 �ٲ� 
//���� ���� å �뿩������ �ǳ� ���� ������ å �߰����ָ� ���� ��������. =>�ݺ����� ���� ������ȣ�� ������ �ʵ��� 
//08-20 �뿩����� ������ȣ�� �������� �ٲٰ� �������� yn�� 0�� �Ǵ°��̶� �����̶� ��ġ ��Ų��. 
//08-21 �뿩������ ���� �ٲ�� �ȴ�.(�뿩����� ������ȣ���� ���� å�� �����ҋ�)(�� ȸ������ �뿩�� ������ȣ���� �ٲ�°� )
//������ ���¿��� ���������� ���ĺκп��� ��Ų��. 
//0825 �뿩��Ϻ��� ������ȣ�� ū�� ���� �ҋ� �뿩����� ������ȣ�� �ٲ�������. 

//0827 ȸ���� ����å�� ��������� ������ ������ ������ ������ȣ�� �� å�� ������ ������ȣ ������ ���� ��������. 

//5 6 10 12 13
//5 6 9  11 12
//5 6 9  

//2 3
//1 2
//2 2

//3 5 8 4 7 9 		6�� �������� 
//3 5 7 4 6 8
//3 5 8 4 7 8
void isbnsort2(int temp_sort_num){//�뿩����� ������ȣ�� ���� �� �ٲ��. 
	int i,j;
	int count = 0;
	int nsort_num = 0;
	for(i=0;i<numofborrow;i++){
		if(g_borrow[i]->rdate[1]!=g_borrow[i]->date[1]){
			if(g_borrow[i]->sort_num>temp_sort_num){
				g_borrow[i]->sort_num-=1;
			}
		}
	}
	for(i=0;i<numofbook;i++){
		g_book[i]->sort_num = i+1;
	}
}
void isbnsort(){//ȸ�� 1�� å 1 2�� ������ å 1 2 �� ����ؼ�  ȸ��2�� å 1 2�� ������ ȸ�� 1�� å 1�� 2�� ������ ȸ�� 2�� å 2�� 2�� ������. 
	int i,j,k;
	k = 0;
	int count = 0;
	int nsort_num = 0;
	BOOK *temp;
	for(i=0;i<numofbook;i++){
		for(j=0;j<numofbook;j++){
			if(strcmp(g_book[i]->ISBN,g_book[j]->ISBN)<0){
				temp = g_book[i];
				g_book[i] = g_book[j];
				g_book[j] = temp; 
			}
		}
	} 
	for(i=0;i<numofborrow;i++){
		if(g_borrow[i]->rdate[1]!=g_borrow[i]->date[1]){
			for(j=0;j<numofbook;j++){
				if(g_book[j]->sort_num==g_borrow[i]->sort_num){
					nsort_num = j+1;
				}
			}
			g_borrow[i]->sort_num = nsort_num;
		}
	}
	for(i=0;i<numofbook;i++){
		g_book[i]->sort_num = i+1;
	}
}
BOOK* onebook(){
	BOOK *t;
	t = (BOOK*)malloc(sizeof(BOOK));
	fflush(stdin);
	printf("å ������ �Է��ϼ���:");
	scanf("%s",t->book_name);
	fflush(stdin);
	printf("���ǻ縦 �Է��ϼ���:");
	scanf("%s",t->maker);
	fflush(stdin);
	printf("���ڸ� �Է��ϼ���:");
	scanf("%s",t->author);
	fflush(stdin);
	printf("ISBN�� �Է��ϼ���:");
	scanf("%s",t->ISBN);
	fflush(stdin);
	printf("����ó�� �Է��ϼ���:");
	scanf("%s",t->place);
	fflush(stdin);
	t->yn = 1;
	t->sort_num = numofbook+1;
	return t;
}
void bookup(){
	BOOK *temp;
	temp = onebook();
	if(numofbook==0){
		g_book[0]=(BOOK*)malloc(sizeof(BOOK));
	}
	else{
		g_book = (BOOK**)realloc(g_book,(numofbook+1)*sizeof(BOOK*));
	}
	g_book[numofbook] = temp;
	numofbook++;
	isbnsort();
}
void borrow_or_before_deletebook_info(char *bn_or_isbn){
	int i;
	for(i=0;i<numofbook;i++){
		if((strcmp(g_book[i]->book_name,bn_or_isbn)==0)||(strcmp(g_book[i]->ISBN,bn_or_isbn)==0)){
			printf("å ����:%s ���ǻ�:%s ����:%s ISBN:%s ����ó:%s  �뿩���ɿ���:%d �����Ϸù�ȣ:%d\n",g_book[i]->book_name,g_book[i]->maker,g_book[i]->author,g_book[i]->ISBN,g_book[i]->place,g_book[i]->yn,g_book[i]->sort_num);
		}
	}
}
void real_delete(int index){
	int i,j;
	for(i=index;i<numofbook;i++){
		if(i<numofbook-1){
			for(j=i+1;j<i+2;j++){
				g_book[i] = g_book[j];
				g_book[i]->sort_num-=1;
			}
		}
	}
	g_book = (BOOK**)realloc(g_book,(numofbook-1)*sizeof(BOOK*));
	numofbook--;
	printf("������ �����Ǿ����ϴ�!!!\n");
}
void deletebook(){
	int i;
	int temp_sort_num = 0;
	int chk = 0;
	int count = 0;
	char nbn[20],nisbn[20];
	int ndelete_sort_num;
	printf(">> ���� ���� <<\n");
	printf("1.������ �˻� 2.ISBN �˻�\n");
	int opt;
	printf("��ȣ�� �Է��ϼ���:");
	scanf("%d",&opt);
	if(opt==1){
		printf("������ �Է�:");
		scanf("%s",nbn);
		borrow_or_before_deletebook_info(nbn);
	}
	else if(opt==2){
		printf("ISBN �Է�:");
		scanf("%s",nisbn);
		borrow_or_before_deletebook_info(nisbn);
	}
	printf("������ ������ �����Ϸù�ȣ�� �Է��ϼ���:");
	scanf("%d",&ndelete_sort_num);
	for(i=0;i<numofbook;i++){
		if((strcmp(g_book[i]->book_name,nbn)==0)||(strcmp(g_book[i]->ISBN,nisbn)==0)){
			if(g_book[i]->sort_num==ndelete_sort_num){
				if(g_book[i]->yn==1){
					chk = 1;
					temp_sort_num = g_book[i]->sort_num;
					real_delete(i);
				}
			}
		}
	}
	if(chk==1){
		isbnsort2(temp_sort_num);
	}
}

void bookshow(char* any){
	int i;
	for(i=0;i<numofbook;i++){
		if((strcmp(any,g_book[i]->book_name)==0)||(strcmp(any,g_book[i]->maker)==0)||(strcmp(any,g_book[i]->ISBN)==0)||(strcmp(any,g_book[i]->author)==0)){
			printf("å �Ϸù�ȣ:%d\n",g_book[i]->sort_num);
			printf("å �̸�:%s\n",g_book[i]->book_name);
			printf("å ���ǻ�:%s\n",g_book[i]->maker);
			printf("å ����:%s\n",g_book[i]->author);
			printf("å ISBN:%s\n",g_book[i]->ISBN);
			printf("å ����ó:%s\n",g_book[i]->place);
		}
	}
}
void totalsearch(){
	int i;
	for(i=0;i<numofbook;i++){
		printf("å����:%s ���ǻ�:%s ����:%s ISBN:%s ����ó:%s �뿩���ɿ���:%d �����Ϸù�ȣ:%d\n",g_book[i]->book_name,g_book[i]->maker,g_book[i]->author,g_book[i]->ISBN,g_book[i]->place,g_book[i]->yn,g_book[i]->sort_num); 
	}

}

void booknamesearch(){
	char nbn[20];
	printf("�������Է�:"); 
	scanf("%s",nbn);
	bookshow(nbn);
}
void makersearch(){
	char nm[20];
	printf("���ǻ��Է�:"); 
	scanf("%s",nm);
	bookshow(nm);
}
void isbnsearch(){
	char nisbn[20];
	printf("ISBN �Է�:"); 
	scanf("%s",nisbn);
	bookshow(nisbn);
}
void authorsearch(){
	char nau[20];
	printf("���� �Է�:"); 
	scanf("%s",nau);
	bookshow(nau);
} 
void booksearch(){
	enum BOOKSEARCHMENU m = booksearchmenu();
	switch(m){
		case BOOKNAMESEARCH:
			booknamesearch();
			break;
		case MAKERSEARCH:
			makersearch();
			break;
		case ISBNSEARCH:
			isbnsearch();
			break;
		case AUTHORSEARCH:
			authorsearch();
			break;
		case EVERYTHINGSEARCH:
			totalsearch();
			break;
		case EXIT:
			break;
		default:
			error();
			break; 
	}
}
