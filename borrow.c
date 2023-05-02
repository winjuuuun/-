#include "common.h"
#include "client.h"
#include "book.h"
#include "borrow.h"
#include "admin.h"
#include "fileio.h"
#include "screenui.h"
//대여해줄떄 없는 책,학번,도서번호 사람에게 책을 빌려주면 다운된다. 
//반납일자 설정해주기 
//반납일자가 바뀌지 않는다. 
extern CLIENT **g_client;
extern BOOK **g_book;
extern BORROW **g_borrow;
extern int numofclient;
extern int numofbook;
extern int numofborrow;
int sortnum_chk(char *temp,int sortnum){
	int i;
	int ans = 0;
	for(i=0;i<numofbook;i++){
		if((strcmp(g_book[i]->book_name,temp)==0)||(strcmp(g_book[i]->ISBN,temp)==0)){
			if(g_book[i]->sort_num==sortnum)ans = 1;
		}
	}
	return ans;
} 
int studentnum_chk(char *studentnum){
	int i;
	int ans = 0;
	for(i=0;i<numofclient;i++){
		if(strcmp(g_client[i]->student_num,studentnum)==0)ans = 1;
	}
	return ans;
} 
int isbn_chk(char *isbn){
	int i;
	int ans = 0;
	for(i=0;i<numofbook;i++){
		if(strcmp(g_book[i]->ISBN,isbn)==0)ans = 1;
	}
	return ans;
} 
int bookname_chk(char *bookname){
	int i;
	int ans = 0;
	for(i=0;i<numofbook;i++){
		if(strcmp(g_book[i]->book_name,bookname)==0)ans = 1;
	}
	return ans;
} 
void tttimer(int *tar){
	struct tm *t;
	time_t timer;
	timer = time(NULL);
	t = localtime(&timer);
	tar[0] = t->tm_year+1900;
	tar[1] = t->tm_mon+1;
	tar[2] = t->tm_mday+1;
	tar[3] = t->tm_hour+1;
	tar[4] = t->tm_min+1;
	tar[5] = t->tm_sec+1;
}
BORROW* oneborrow(){//대여 해준것을 다른사람들에게 대여해주고 있다. t에 null로 초기화했는데 대여여부 묻는 조건문에 오기까지 t의 값이 바껴있다. 
	int i,j,k;
	int truep = 0;
	BORROW *t;
	t = NULL;
	char temp[20];
	char nstudent_num[20];
	int nsort_num;
	char nbn[20],nisbn[20]; 
	printf(">> 대여할 도서 <<\n");
	printf("1.도서명 검색 2.ISBN 검색\n");
	int opt;
	printf("번호를 입력하세요:");
	scanf("%d",&opt);
	if(opt==1){
		printf("도서명 입력:");
		scanf("%s",nbn);
		if(bookname_chk(nbn)==0)return;
		strcpy(temp,nbn);
		borrow_or_before_deletebook_info(nbn);
	}
	else if(opt==2){
		printf("ISBN 입력:");
		scanf("%s",nisbn);
		if(isbn_chk(nisbn)==0)return;
		strcpy(temp,nisbn);
		borrow_or_before_deletebook_info(nisbn);
	}
	printf("학번을 입력하세요:");
	scanf("%s",nstudent_num);
	if(studentnum_chk(nstudent_num)==0)return;
	fflush(stdin);
	printf("도서일련번호를 입력하세요:");
	scanf("%d",&nsort_num);
	if(sortnum_chk(temp,nsort_num)==0)return;
	for(i=0;i<numofbook;i++){
		if(strcmp(g_book[i]->book_name,nbn)==0||strcmp(g_book[i]->ISBN,nisbn)==0){		//책제목 비교	
			if((nsort_num==g_book[i]->sort_num)&&(g_book[i]->yn==1)){//도서번호 같은지 
				t = (BORROW*)malloc(sizeof(BORROW));
				strcpy(t->student_num,nstudent_num);
				t->borrow_sort_num = numofborrow+1;
				t->sort_num = g_book[i]->sort_num;
				g_book[i]->yn = 0;
				tttimer(t->date);
				for(k=0;k<6;k++){
					t->rdate[k] = t->date[k];
				}
				t->rdate[1]+=1;
			}	
		}
	}
	return t;
}
void borrowon(){
	BORROW *temp;
	temp = oneborrow();
	if(temp==NULL)return;
	if(numofborrow==0){
		g_borrow[0] = (BORROW*)malloc(sizeof(BORROW));
	}
	else{
		g_borrow = (BORROW**)realloc(g_borrow,(numofborrow+1)*sizeof(BORROW*));
	}
	g_borrow[numofborrow] = temp;
	printf("도서가 대여되었습니다.\n"); 
	numofborrow++;
}
void borrowing_list(char *nstudent_num){//반납한 책도 출력되고 있다.(반납하고 다시 빌렸을때 그 책의 이전 기록이 대여한 목록에 뜬다.)  -->반납일자가 0일떄만 출력시키기 
	int i,j,k;
	if(strcmp(nstudent_num,"admin")==0){
		for(i=0;i<numofborrow;i++){
			for(j=0;j<numofbook;j++){
				if(g_book[j]->yn==0){
					if(g_borrow[i]->sort_num==g_book[j]->sort_num){
						if(g_borrow[i]->rdate[1]!=g_borrow[i]->date[1]){
							printf("학번:%s\n",g_borrow[i]->student_num);
							printf("대여순번:%d\n",g_borrow[i]->borrow_sort_num);
							printf("도서일련번호:%d\n",g_borrow[i]->sort_num);
							printf("대여일자 :"); 
								for(k=0;k<6;k++){
									printf("%d ",g_borrow[i]->date[k]);
								}
								printf("반납일자 :"); 
								for(k=0;k<6;k++){
									printf("%d ",g_borrow[i]->rdate[k]);
								}
						}
					}
				}
			}
			printf("\n");
		}
	}
	else{
		for(i=0;i<numofborrow;i++){
			for(j=0;j<numofbook;j++){
				if(g_book[j]->yn==0){
					if(g_borrow[i]->sort_num==g_book[j]->sort_num){
						if(strcmp(g_borrow[i]->student_num,nstudent_num)==0){
							if(g_borrow[i]->rdate[1]!=g_borrow[i]->date[1]){
								printf("학번:%s\n",g_borrow[i]->student_num);
								printf("대여순번:%d\n",g_borrow[i]->borrow_sort_num);
								printf("도서일련번호:%d\n",g_borrow[i]->sort_num);
								printf("대여일자 :"); 
									for(k=0;k<6;k++){
										printf("%d ",g_borrow[i]->date[k]);
									}
									printf("반납일자 :"); 
									for(k=0;k<6;k++){
										printf("%d ",g_borrow[i]->rdate[k]);
									}
							}
						}
					}
				}
			}
			printf("\n");
		}
	}
}

void showborrowlist(){
	int i,j;
	if(numofborrow==0){
		return;
	}
	else{
		for(i=0;i<numofborrow;i++){
				printf("학번:%s\n",g_borrow[i]->student_num);
				printf("대여순번:%d\n",g_borrow[i]->borrow_sort_num);
				printf("도서일련번호:%d\n",g_borrow[i]->sort_num);
				printf("대여일자 :"); 
				for(j=0;j<6;j++){
					printf("%d ",g_borrow[i]->date[j]);
				}
				printf("반납일자 :"); 
				for(j=0;j<6;j++){
					printf("%d ",g_borrow[i]->rdate[j]);
				}
				printf("\n");
		}
	}
}					
void bookreturn(){
 	int i,j,k;
 	int chk = 0;
 	int truep=0;
 	int sn_chk=0;
 	char nstudent_num[20];
 	int nsort_num;
 	printf("학번을 입력하세요:");
	scanf("%s",nstudent_num);
	for(i=0;i<numofborrow;i++){
		if((strcmp(g_borrow[i]->student_num,nstudent_num)==0)||(strcmp(nstudent_num,"admin")==0))sn_chk=1;
	}
	if(sn_chk!=1)return;
	borrowing_list(nstudent_num); 
	if(strcmp(nstudent_num,"admin")==0)return;
	printf("반납할 도서번호를 입력하세요:");
	scanf("%d",&nsort_num);
	//여기서 다운 된다.
	for(i=0;i<numofborrow;i++){//다른 사람 대여한것도 반납하고 있다. 
		if((g_borrow[i]->sort_num==nsort_num)&&(strcmp(g_borrow[i]->student_num,nstudent_num)==0)){
			chk = 1;
			for(j=0;j<numofbook;j++){
				if(g_book[j]->sort_num==nsort_num){
					g_book[j]->yn = 1;
					break;
				}
			}
		}
	}
	if(chk==0){
		printf("대여목록에 없습니다.\n");
		return;
	}
	for(i=0;i<numofborrow;i++){
		if(g_borrow[i]->rdate[1]!=g_borrow[i]->date[1]){
			if(g_borrow[i]->sort_num==nsort_num){
				tttimer(g_borrow[i]->rdate);
				printf("도서가 반납되었습니다.\n"); 
				break;
			}
		}
	}
}
