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
			printf("�뿩��Ͽ� �ִ� ȸ���Դϴ�!!!\n");
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
		printf("�й��� �Է��ϼ���:");
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
	printf("��й�ȣ�� �Է��ϼ���:");
	scanf("%s",t->password);
	printf("�̸��� �Է��ϼ���:");
	scanf("%s",t->name);
	printf("�ּҸ� �Է��ϼ���:");
	scanf("%s",t->addr);
	while(1){
		printf("��ȭ��ȣ�� �Է��ϼ���:");
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
	printf("������ id:admin\n");
	printf("������ ��й�ȣ:1234\n");
	printf("�й��� �Է��ϼ���:");
	scanf("%s",nsn);
	printf("��й�ȣ�� �Է��ϼ���:");
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
	printf("�α׾ƿ� �Ǿ����ϴ�.\n");
}
void client_logout(char *id,char *pw){
	strcpy(id,"");
	strcpy(pw,"");
	printf("�α׾ƿ��Ǿ����ϴ�.\n");
}
void everything_search(){
	int i;
	for(i=0;i<numofclient;i++){
			printf("%s�� ����>>\n",g_client[i]->name);
			printf("�й�:%s\n",g_client[i]->student_num);
			printf("��й�ȣ:%s\n",g_client[i]->password);
			printf("�̸�:%s\n",g_client[i]->name);
			printf("�ּ�:%s\n",g_client[i]->addr);
			printf("��ȭ��ȣ:%s\n",g_client[i]->phone_num);
			printf("\n");
	}
}
void student_num_search(){
	int i;
	char nnum[20];
	printf("�й��� �Է��ϼ���:");
	scanf("%s",nnum);
	for(i=0;i<numofclient;i++){
		if(strcmp(g_client[i]->student_num,nnum)==0){
			printf("�й�:%s\n",g_client[i]->student_num);
			printf("��й�ȣ:%s\n",g_client[i]->password);
			printf("�̸�:%s\n",g_client[i]->name);
			printf("�ּ�:%s\n",g_client[i]->addr);
			printf("��ȭ��ȣ:%s\n",g_client[i]->phone_num);
		}
	}
}
void name_search(){
	int i;
	char nn[20];
	printf("�̸��� �Է��ϼ���:");
	scanf("%s",nn);
	for(i=0;i<numofclient;i++){
		if(strcmp(g_client[i]->name,nn)==0){
			printf("�й�:%s\n",g_client[i]->student_num);
			printf("��й�ȣ:%s\n",g_client[i]->password);
			printf("�̸�:%s\n",g_client[i]->name);
			printf("�ּ�:%s\n",g_client[i]->addr);
			printf("��ȭ��ȣ:%s\n",g_client[i]->phone_num);
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
			printf("�й�:%s�Դϴ�.\n",g_client[i]->student_num); 
			
			printf("��й�ȣ:%s�Դϴ�. �����Ͻðڽ��ϱ�?(�ٲ� ��� �Է�)",g_client[i]->password); 
			scanf("%s",modify);
			if(strcmp(modify,g_client[i]->password)!=0){
				strcpy(g_client[i]->password,modify);
			}
		
			printf("�̸�:%s�Դϴ�.\n",g_client[i]->name); 
			
			printf("�ּ�:%s�Դϴ�. �����Ͻðڽ��ϱ�?(�ٲ� �ּ� �Է�)",g_client[i]->addr);
			scanf("%s",modify);
			if(strcmp(modify,g_client[i]->addr)!=0){
				strcpy(g_client[i]->addr,modify);
			}
			
			printf("��ȭ��ȣ:%s�Դϴ�. �����Ͻðڽ��ϱ�?(�ٲ� ��ȣ �Է�)",g_client[i]->phone_num);  
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
	printf("ȸ��Ż��Ǿ����ϴ�!!!\n");
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
					 	printf("�ݳ����� ���� ������ �ֽ��ϴ�.\n");
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
			printf("�α׾ƿ������Դϴ�!!!\n"); 
			return;
		}
		enum CLIENTMENU opt = clientmenu();
		if(opt==5)break;
		switch(opt){
			case SEARCHBOOK:
				booksearch();
				break;
			case RENTLIST:
				client_rentlist(id);//��������
				break;
			case FIXINFO:
				client_info_fix(id);
				break;
			case SIGNOUT:
				signout(id,pw);//��������
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
