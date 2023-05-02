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
//파일 읽기:할당 재할당하면서 파일 읽기 
//프로그램 끝날떄 파일 쓰고 시작할떄 불려오기 
void f_write(){ 
	FILE *ofp;
	ofp = fopen("client.txt","w");
	int i,j;
	for(i=0;i<numofclient;i++){
		fprintf(ofp,"%s %s %s %s %s\n",g_client[i]->student_num,g_client[i]->password,g_client[i]->name,g_client[i]->addr,g_client[i]->phone_num);
	}
	fclose(ofp);
	ofp = fopen("book.txt","w");
	for(i=0;i<numofbook;i++){
		fprintf(ofp,"%s %s %s %s %s %d %d\n",g_book[i]->book_name,g_book[i]->maker,g_book[i]->author,g_book[i]->ISBN,g_book[i]->place,g_book[i]->yn,g_book[i]->sort_num);
	}
	fclose(ofp);
	ofp = fopen("borrow.txt","w");
	for(i=0;i<numofborrow;i++){
		fprintf(ofp,"%s %d %d ",g_borrow[i]->student_num,g_borrow[i]->borrow_sort_num,g_borrow[i]->sort_num); 
		for(j=0;j<6;j++){
			fprintf(ofp,"%d ",g_borrow[i]->date[j]);
		} 
		for(j=0;j<6;j++){
			fprintf(ofp,"%d ",g_borrow[i]->rdate[j]);
		}
		fprintf(ofp,"\n");
	}
	fclose(ofp);
}
//파일에서 읽어온값을 전역변수들에 넣어주기 
//포인터배열에 직접 값을 못 담는다. 그러므로  하나의 구조체를 할당해주고 연결 해주기(파일에서 하나 읽어서 구조체 하나를 리턴해주는 함수 만들기) 
//함수화해야하는 이유:파일에서 읽어올떄 변수를 계속 만들어줘야해서 함수화안하면 마지막꺼하나밖에 기억 못함 

//파일끝일떄 알려줘야한다. 
CLIENT* tempclient(FILE *ifp){//파일 끝이면 리턴값에 널을 넣기 
	int res; 
	CLIENT *t;
	t = (CLIENT*)malloc(sizeof(CLIENT));
	res = fscanf(ifp,"%s %s %s %s %s\n",t->student_num,t->password,t->name,t->addr,t->phone_num);
	if(res==EOF)t = NULL;
	return t;
}
BOOK* tempbook(FILE *ifp){//파일 끝이면 리턴값에 널을 넣기 
	int res; 
	BOOK *t;
	t = (BOOK*)malloc(sizeof(BOOK));
	res = fscanf(ifp,"%s %s %s %s %s %d %d\n",t->book_name,t->maker,t->author,t->ISBN,t->place,&t->yn,&t->sort_num);
	if(res==EOF)t = NULL;
	return t;
}
BORROW* tempborrow(FILE *ifp){//파일 끝이면 리턴값에 널을 넣기 
	int res; 
	int i;
	BORROW *t;
	t = (BORROW*)malloc(sizeof(BORROW));
	res = 	fscanf(ifp,"%s %d %d ",t->student_num,&t->borrow_sort_num,&t->sort_num);
	for(i=0;i<6;i++){
		fscanf(ifp,"%d ",&t->date[i]);
	}
	for(i=0;i<6;i++){
		fscanf(ifp,"%d ",&t->rdate[i]);
	}
	if(res==EOF)t = NULL;
	return t;
}
void f_read(){//갑이 널일떈 구조체에 넣지 말기 
	CLIENT *temp;
	BOOK *temp2;
	BORROW *temp3;
	FILE *ifp;
	int i = 0; 
	ifp = fopen("client.txt","r");
	while(1){
		temp = tempclient(ifp); 
		if(temp==NULL)break;
		if(numofclient==0){
			g_client[0] = (CLIENT*)malloc(sizeof(CLIENT));
		}
		else{
			g_client = (CLIENT**)realloc(g_client,(numofclient+1)*sizeof(CLIENT*));
		}
		g_client[i] = temp;
		numofclient++;
		i++;
	}
	fclose(ifp);
	i = 0;
	ifp = fopen("book.txt","r");
	while(1){
		temp2 = tempbook(ifp); 
		if(temp2==NULL)break;
		if(numofbook==0){
			g_book[0] = (BOOK*)malloc(sizeof(BOOK));
		}
		else{
			g_book = (BOOK**)realloc(g_book,(numofbook+1)*sizeof(BOOK*));
		}
		g_book[i] = temp2;
		numofbook++;
		i++;
	}
	fclose(ifp);
	i = 0;
	ifp = fopen("borrow.txt","r");
	while(1){
		temp3 = tempborrow(ifp); 
		if(temp3==NULL)break;
		if(numofborrow==0){
			g_borrow[0] = (BORROW*)malloc(sizeof(BORROW));
		}
		else{
			g_borrow = (BORROW**)realloc(g_borrow,(numofborrow+1)*sizeof(BORROW*));
		}
		g_borrow[i] = temp3;
		numofborrow++;
		i++;
	}
	fclose(ifp);
}
	
