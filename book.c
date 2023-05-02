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

//도서에서 대여의 도서 일련번호가 바뀔지 판단 만약 바꿔야한다면 대여목록의 도서번호를 먼저 바꾸기 -> 도서에서 도서번호 바꾸기 
//==>추가한 책의 ISBN이 대여한 책들의 ISBN보다 크다면 대여한 책의 도서번호가 안 바뀌고 반대일 경우만 바뀜 
//같은 제목 책 대여까지는 되나 같은 제목의 책 추가해주면 덮어 씌어진다. =>반복문에 같은 도서번호가 들어오지 않도록 
//08-20 대여목록의 도서번호를 순번으로 바꾸고 도서에서 yn이 0이 되는곳이랑 순번이랑 매치 시킨다. 
//08-21 대여순번이 서로 바뀌게 된다.(대여목록의 도서번호보다 작은 책을 삭제할떄)(각 회원들의 대여한 도서번호끼리 바뀌는것 )
//빌려준 상태에서 지워줬을때 정렬부분에서 엉킨다. 
//0825 대여목록보다 도서번호가 큰걸 삭제 할떄 대여목록의 도서번호가 바껴버린다. 

//0827 회원이 여러책을 빌렸을경우 삭제를 연속을 했을때 도서번호가 각 책의 마지막 도서번호 값으로 덮어 씌워진다. 

//5 6 10 12 13
//5 6 9  11 12
//5 6 9  

//2 3
//1 2
//2 2

//3 5 8 4 7 9 		6을 지웠을때 
//3 5 7 4 6 8
//3 5 8 4 7 8
void isbnsort2(int temp_sort_num){//대여목록의 도서번호가 서로 뒤 바뀐다. 
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
void isbnsort(){//회원 1이 책 1 2를 빌리고 책 1 2 를 등록해서  회원2가 책 1 2를 빌리면 회원 1이 책 1을 2개 가지고 회원 2가 책 2를 2개 가진다. 
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
	printf("책 제목을 입력하세요:");
	scanf("%s",t->book_name);
	fflush(stdin);
	printf("출판사를 입력하세요:");
	scanf("%s",t->maker);
	fflush(stdin);
	printf("저자를 입력하세요:");
	scanf("%s",t->author);
	fflush(stdin);
	printf("ISBN을 입력하세요:");
	scanf("%s",t->ISBN);
	fflush(stdin);
	printf("소장처를 입력하세요:");
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
			printf("책 제목:%s 출판사:%s 저자:%s ISBN:%s 소장처:%s  대여가능여부:%d 도서일련번호:%d\n",g_book[i]->book_name,g_book[i]->maker,g_book[i]->author,g_book[i]->ISBN,g_book[i]->place,g_book[i]->yn,g_book[i]->sort_num);
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
	printf("도서가 삭제되었습니다!!!\n");
}
void deletebook(){
	int i;
	int temp_sort_num = 0;
	int chk = 0;
	int count = 0;
	char nbn[20],nisbn[20];
	int ndelete_sort_num;
	printf(">> 도서 삭제 <<\n");
	printf("1.도서명 검색 2.ISBN 검색\n");
	int opt;
	printf("번호를 입력하세요:");
	scanf("%d",&opt);
	if(opt==1){
		printf("도서명 입력:");
		scanf("%s",nbn);
		borrow_or_before_deletebook_info(nbn);
	}
	else if(opt==2){
		printf("ISBN 입력:");
		scanf("%s",nisbn);
		borrow_or_before_deletebook_info(nisbn);
	}
	printf("삭제할 도서의 도서일련번호를 입력하세요:");
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
			printf("책 일련번호:%d\n",g_book[i]->sort_num);
			printf("책 이름:%s\n",g_book[i]->book_name);
			printf("책 출판사:%s\n",g_book[i]->maker);
			printf("책 저자:%s\n",g_book[i]->author);
			printf("책 ISBN:%s\n",g_book[i]->ISBN);
			printf("책 소장처:%s\n",g_book[i]->place);
		}
	}
}
void totalsearch(){
	int i;
	for(i=0;i<numofbook;i++){
		printf("책제목:%s 출판사:%s 저자:%s ISBN:%s 소장처:%s 대여가능여부:%d 도서일련번호:%d\n",g_book[i]->book_name,g_book[i]->maker,g_book[i]->author,g_book[i]->ISBN,g_book[i]->place,g_book[i]->yn,g_book[i]->sort_num); 
	}

}

void booknamesearch(){
	char nbn[20];
	printf("도서명입력:"); 
	scanf("%s",nbn);
	bookshow(nbn);
}
void makersearch(){
	char nm[20];
	printf("출판사입력:"); 
	scanf("%s",nm);
	bookshow(nm);
}
void isbnsearch(){
	char nisbn[20];
	printf("ISBN 입력:"); 
	scanf("%s",nisbn);
	bookshow(nisbn);
}
void authorsearch(){
	char nau[20];
	printf("저자 입력:"); 
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
