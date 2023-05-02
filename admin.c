#include "common.h"
#include "client.h"
#include "book.h"
#include "borrow.h"
#include "admin.h"
#include "fileio.h"
#include "screenui.h"

int admin_menu(char *id,char *pw){
	while(1){
		if((strcmp(id,"")==0)&&(strcmp(pw,"")==0)){
			printf("로그아웃상태입니다.\n");
			return;
		}
	 enum ADMINMENU	m = adminmenu();
	 if(m==8)break;
		switch(m){
			case BOOKUP:
				bookup();
				break;
			case BOOKDELETE:
				deletebook();
				break;
			case BOOKRENT:
				borrowon();
				break;
			case BOOKRETURN:
				bookreturn();
				break;
			case BOOKSEARCH:
				booksearch();
				break;
			case CLIENTLIST:
				clientlist();
				break;
			case SHOWBORROWLIST:
				showborrowlist();
				break;
			case ADMINLOGOUT:
				admin_logout(id,pw);
				break;
			case ADMINPROGRAMOUT:
				break;
			default:
				error();
				break;
		}
		if(m==ADMINPROGRAMOUT){
			return 1;
		}
		f_write();
	}
}
