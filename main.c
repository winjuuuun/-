#include "common.h"
#include "client.h"
#include "book.h"
#include "borrow.h"
#include "admin.h"
#include "fileio.h"
#include "screenui.h"
//�ݳ� ��ġ�� ->8/6 �ݳ� �Ϸ� 
//å�� isbn���� �����ϱ� 
//���� �д°� �ȵȴ�. 
CLIENT **g_client;
int numofclient=0;

BOOK **g_book;
int numofbook=0;


BORROW **g_borrow;
int numofborrow=0;

int main() {
	int ans;
	g_client = (CLIENT **)malloc(sizeof(CLIENT*));
	g_book = (BOOK **)malloc(sizeof(BOOK*));
	g_borrow = (BORROW **)malloc(sizeof(BORROW*));
	
	enum MAINMENU m;
	
	char adminid[10] = "admin";
	char adminpassword[10] = "1234";
	
	f_read();
	
	while((m=mainmenu())!=QUIT){
		switch(m){
			case JOIN:
				signup();
				f_write();
				break;
			case LOGIN:
				ans = login();
				break;
			default:
				error();
				break;
		}
		if(ans==1)break;
	}
	return 0;
}
