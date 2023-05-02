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
void student_num_sort(){
	int i,j;
	CLIENT *temp;
	for(i=0;i<numofclient;i++){
		for(j=0;j<numofclient;j++){
			if(strcmp(g_client[i]->student_num,g_client[j]->student_num)<0){
				temp = g_client[i];
				g_client[i] = g_client[j];
				g_client[j] = temp;
			}
		}
	}
}
int checkclient_borrow_exist(char *nstudentn){
	int i;
	for(i=0;i<numofborrow;i++){
		if(strcmp(g_borrow[i]->student_num,nstudentn)==0){
			printf("대여목록에 있는 회원입니다!!!\n");
			return 1;
		}
	}
	return 0;
}
CLIENT* onesign(){
	int i,ch; 
	char nn[20];
	CLIENT *t;
	t = (CLIENT*)malloc(sizeof(CLIENT));
	while(1){
		printf("학번을 입력하세요:");
		scanf("%s",nn);
		if(checkclient_borrow_exist(nn)==1)continue;
		ch = 0;
		for(i=0;i<numofclient;i++){
			if(strcmp(nn,g_client[i]->student_num)==0){
				ch=1;
			}
		}
		if(ch==0){
			strcpy(t->student_num,nn);
			break;
		}
	}
	printf("비밀번호를 입력하세요:");
	scanf("%s",t->password);
	printf("이름을 입력하세요:");
	scanf("%s",t->name);
	printf("주소를 입력하세요:");
	scanf("%s",t->addr);
	while(1){
		printf("전화번호를 입력하세요:");
		scanf("%s",nn);
		ch = 0;
		for(i=0;i<numofclient;i++){
			if(strcmp(nn,g_client[i]->phone_num)==0){
				ch=1;
			}
		}
		if(ch==0){
			strcpy(t->phone_num,nn);
			break;
		}
	}
	return t;
}
void signup(){
	CLIENT *temp;
	temp = onesign();
	if(numofclient==0){
		g_client[0] = (CLIENT*)malloc(sizeof(CLIENT));
	}
	else{
		g_client = (CLIENT**)realloc(g_client,(numofclient+1)*sizeof(CLIENT*));
	}
	g_client[numofclient] = temp;
	numofclient++;
	student_num_sort();
}
int login(){
	int i;
	int ans;
	int ans2;
	int opt = 0;
	char nsn[10],npw[10];
	printf("관리자 id:admin\n");
	printf("관리자 비밀번호:1234\n");
	printf("학번을 입력하세요:");
	scanf("%s",nsn);
	printf("비밀번호를 입력하세요:");
	scanf("%s",npw);
	if((strcmp(nsn,"admin")==0)&&(strcmp(npw,"1234")==0)){
		ans = admin_menu("admin","1234");
		if(ans==1)return 1;
	}
	else{
		for(i=0;i<numofclient;i++){
			if((strcmp(nsn,g_client[i]->student_num)==0)&&(strcmp(npw,g_client[i]->password)==0)){
				opt = 1;
			}
		}
		if(opt==1){
			ans2 = clientservice(nsn,npw);
			if(ans2==1)return 1;
		}
		else{
			error();
		}
	}
}
void admin_logout(char *id,char *pw){
	strcpy(id,"");
	strcpy(pw,"");
	printf("로그아웃 되었습니다.\n");
}
void client_logout(char *id,char *pw){
	strcpy(id,"");
	strcpy(pw,"");
	printf("로그아웃되었습니다.\n");
}
void everything_search(){
	int i;
	for(i=0;i<numofclient;i++){
			printf("%s의 정보>>\n",g_client[i]->name);
			printf("학번:%s\n",g_client[i]->student_num);
			printf("비밀번호:%s\n",g_client[i]->password);
			printf("이름:%s\n",g_client[i]->name);
			printf("주소:%s\n",g_client[i]->addr);
			printf("전화번호:%s\n",g_client[i]->phone_num);
			printf("\n");
	}
}
void student_num_search(){
	int i;
	char nnum[20];
	printf("학번을 입력하세요:");
	scanf("%s",nnum);
	for(i=0;i<numofclient;i++){
		if(strcmp(g_client[i]->student_num,nnum)==0){
			printf("학번:%s\n",g_client[i]->student_num);
			printf("비밀번호:%s\n",g_client[i]->password);
			printf("이름:%s\n",g_client[i]->name);
			printf("주소:%s\n",g_client[i]->addr);
			printf("전화번호:%s\n",g_client[i]->phone_num);
		}
	}
}
void name_search(){
	int i;
	char nn[20];
	printf("이름을 입력하세요:");
	scanf("%s",nn);
	for(i=0;i<numofclient;i++){
		if(strcmp(g_client[i]->name,nn)==0){
			printf("학번:%s\n",g_client[i]->student_num);
			printf("비밀번호:%s\n",g_client[i]->password);
			printf("이름:%s\n",g_client[i]->name);
			printf("주소:%s\n",g_client[i]->addr);
			printf("전화번호:%s\n",g_client[i]->phone_num);
		}
	}
}
void clientlist(){
	enum CLIENTSUBMENU m = clientsubmenu();
	switch(m){
		case NAME:
			name_search();
			break;
		case STUDENT_NUM:
			student_num_search();
			break;
		case EVERYTHING:
			everything_search();
			break;
		default:
			error();
			break;
	}
}
void client_rentlist(char *id){
	borrowing_list(id);
}
void client_info_fix(char*id){
	int i,j;
	int pn_chk=0;
	char modify[20]; 
	for(i=0;i<numofclient;i++){
		if(strcmp(id,g_client[i]->student_num)==0){
			printf("학번:%s입니다.\n",g_client[i]->student_num); 
			
			printf("비밀번호:%s입니다. 수정하시겠습니까?(바꿀 비번 입력)",g_client[i]->password); 
			scanf("%s",modify);
			if(strcmp(modify,g_client[i]->password)!=0){
				strcpy(g_client[i]->password,modify);
			}
		
			printf("이름:%s입니다.\n",g_client[i]->name); 
			
			printf("주소:%s입니다. 수정하시겠습니까?(바꿀 주소 입력)",g_client[i]->addr);
			scanf("%s",modify);
			if(strcmp(modify,g_client[i]->addr)!=0){
				strcpy(g_client[i]->addr,modify);
			}
			
			printf("전화번호:%s입니다. 수정하시겠습니까?(바꿀 번호 입력)",g_client[i]->phone_num);  
			scanf("%s",modify);
			for(j=0;j<numofclient;j++){
				if(strcmp(g_client[j]->phone_num,modify)==0)pn_chk=1;
			}
			if(pn_chk==0){
				strcpy(g_client[i]->phone_num,modify);
			}
		}
	}
}
void deleteclient(char *id){
	int i,j,loc;
	for(i=0;i<numofclient;i++){
		if(strcmp(id,g_client[i]->student_num)==0)loc = i;
	}
	for(i=loc;i<numofclient;i++){
		if(i<numofclient-1){
			for(j=i+1;j<i+2;j++){
				g_client[i] = g_client[j];
			}
		}
	}
	g_client = (CLIENT**)realloc(g_client,(numofclient-1)*sizeof(CLIENT*));
	numofclient--;
	printf("회원탈퇴되었습니다!!!\n");
}
void signout(char *id,char *pw){
	int i,j;
	int opt = 0;
	for(i=0;i<numofborrow;i++){
		if(strcmp(id,g_borrow[i]->student_num)==0){
			 for(j=0;j<numofbook;j++){
			 	if(g_book[j]->sort_num==g_borrow[i]->sort_num){
			 		if(g_book[j]->yn==0){
			 			opt = 1;
					 	printf("반납하지 않은 도서가 있습니다.\n");
					 }
				}
			}
		}
	}
	if(opt==0){
		deleteclient(id);
	}
	student_num_sort();
}			 		
int clientservice(char *id,char *pw){
	while(1){
		if((strcmp(id,"")==0)&&(strcmp(pw,"")==0)){
			printf("로그아웃상태입니다!!!\n"); 
			return;
		}
		enum CLIENTMENU opt = clientmenu();
		if(opt==5)break;
		switch(opt){
			case SEARCHBOOK:
				booksearch();
				break;
			case RENTLIST:
				client_rentlist(id);//문제있음
				break;
			case FIXINFO:
				client_info_fix(id);
				break;
			case SIGNOUT:
				signout(id,pw);//문제있음
				client_logout(id,pw);
				break;
			case LOGOUT:
				client_logout(id,pw);
				break;
			case PROGRAMOUT:
				break;
			default:
				error();
				break;
		}
		if(opt==PROGRAMOUT){
			return 1;
		}
		f_write();
	}
}
