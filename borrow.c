#include "common.h"
#include "client.h"
#include "book.h"
#include "borrow.h"
#include "admin.h"
#include "fileio.h"
#include "screenui.h"
//�뿩���ً� ���� å,�й�,������ȣ ������� å�� �����ָ� �ٿ�ȴ�. 
//�ݳ����� �������ֱ� 
//�ݳ����ڰ� �ٲ��� �ʴ´�. 
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
BORROW* oneborrow(){//�뿩 ���ذ��� �ٸ�����鿡�� �뿩���ְ� �ִ�. t�� null�� �ʱ�ȭ�ߴµ� �뿩���� ���� ���ǹ��� ������� t�� ���� �ٲ��ִ�. 
	int i,j,k;
	int truep = 0;
	BORROW *t;
	t = NULL;
	char temp[20];
	char nstudent_num[20];
	int nsort_num;
	char nbn[20],nisbn[20]; 
	printf(">> �뿩�� ���� <<\n");
	printf("1.������ �˻� 2.ISBN �˻�\n");
	int opt;
	printf("��ȣ�� �Է��ϼ���:");
	scanf("%d",&opt);
	if(opt==1){
		printf("������ �Է�:");
		scanf("%s",nbn);
		if(bookname_chk(nbn)==0)return;
		strcpy(temp,nbn);
		borrow_or_before_deletebook_info(nbn);
	}
	else if(opt==2){
		printf("ISBN �Է�:");
		scanf("%s",nisbn);
		if(isbn_chk(nisbn)==0)return;
		strcpy(temp,nisbn);
		borrow_or_before_deletebook_info(nisbn);
	}
	printf("�й��� �Է��ϼ���:");
	scanf("%s",nstudent_num);
	if(studentnum_chk(nstudent_num)==0)return;
	fflush(stdin);
	printf("�����Ϸù�ȣ�� �Է��ϼ���:");
	scanf("%d",&nsort_num);
	if(sortnum_chk(temp,nsort_num)==0)return;
	for(i=0;i<numofbook;i++){
		if(strcmp(g_book[i]->book_name,nbn)==0||strcmp(g_book[i]->ISBN,nisbn)==0){		//å���� ��	
			if((nsort_num==g_book[i]->sort_num)&&(g_book[i]->yn==1)){//������ȣ ������ 
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
	printf("������ �뿩�Ǿ����ϴ�.\n"); 
	numofborrow++;
}
void borrowing_list(char *nstudent_num){//�ݳ��� å�� ��µǰ� �ִ�.(�ݳ��ϰ� �ٽ� �������� �� å�� ���� ����� �뿩�� ��Ͽ� ���.)  -->�ݳ����ڰ� 0�ϋ��� ��½�Ű�� 
	int i,j,k;
	if(strcmp(nstudent_num,"admin")==0){
		for(i=0;i<numofborrow;i++){
			for(j=0;j<numofbook;j++){
				if(g_book[j]->yn==0){
					if(g_borrow[i]->sort_num==g_book[j]->sort_num){
						if(g_borrow[i]->rdate[1]!=g_borrow[i]->date[1]){
							printf("�й�:%s\n",g_borrow[i]->student_num);
							printf("�뿩����:%d\n",g_borrow[i]->borrow_sort_num);
							printf("�����Ϸù�ȣ:%d\n",g_borrow[i]->sort_num);
							printf("�뿩���� :"); 
								for(k=0;k<6;k++){
									printf("%d ",g_borrow[i]->date[k]);
								}
								printf("�ݳ����� :"); 
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
								printf("�й�:%s\n",g_borrow[i]->student_num);
								printf("�뿩����:%d\n",g_borrow[i]->borrow_sort_num);
								printf("�����Ϸù�ȣ:%d\n",g_borrow[i]->sort_num);
								printf("�뿩���� :"); 
									for(k=0;k<6;k++){
										printf("%d ",g_borrow[i]->date[k]);
									}
									printf("�ݳ����� :"); 
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
				printf("�й�:%s\n",g_borrow[i]->student_num);
				printf("�뿩����:%d\n",g_borrow[i]->borrow_sort_num);
				printf("�����Ϸù�ȣ:%d\n",g_borrow[i]->sort_num);
				printf("�뿩���� :"); 
				for(j=0;j<6;j++){
					printf("%d ",g_borrow[i]->date[j]);
				}
				printf("�ݳ����� :"); 
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
 	printf("�й��� �Է��ϼ���:");
	scanf("%s",nstudent_num);
	for(i=0;i<numofborrow;i++){
		if((strcmp(g_borrow[i]->student_num,nstudent_num)==0)||(strcmp(nstudent_num,"admin")==0))sn_chk=1;
	}
	if(sn_chk!=1)return;
	borrowing_list(nstudent_num); 
	if(strcmp(nstudent_num,"admin")==0)return;
	printf("�ݳ��� ������ȣ�� �Է��ϼ���:");
	scanf("%d",&nsort_num);
	//���⼭ �ٿ� �ȴ�.
	for(i=0;i<numofborrow;i++){//�ٸ� ��� �뿩�Ѱ͵� �ݳ��ϰ� �ִ�. 
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
		printf("�뿩��Ͽ� �����ϴ�.\n");
		return;
	}
	for(i=0;i<numofborrow;i++){
		if(g_borrow[i]->rdate[1]!=g_borrow[i]->date[1]){
			if(g_borrow[i]->sort_num==nsort_num){
				tttimer(g_borrow[i]->rdate);
				printf("������ �ݳ��Ǿ����ϴ�.\n"); 
				break;
			}
		}
	}
}
