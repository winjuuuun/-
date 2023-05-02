#ifndef _SCREENUI_ 
#define _SCREENUI_
#define error()  printf("잘못입력\n")
#include "common.h"
#include "client.h"
#include "book.h"
#include "borrow.h"
#include "admin.h"
#include "fileio.h"
#include "screenui.h"
// 화면처리 



enum MAINMENU { JOIN=1, LOGIN, QUIT};
enum CLIENTMENU {SEARCHBOOK=1,RENTLIST,FIXINFO,SIGNOUT,LOGOUT,PROGRAMOUT};
enum CLIENTSUBMENU { NAME=1,STUDENT_NUM,EVERYTHING};
enum BOOKSEARCHMENU {BOOKNAMESEARCH=1,MAKERSEARCH,ISBNSEARCH,AUTHORSEARCH,EVERYTHINGSEARCH,EXIT};
enum ADMINMENU { BOOKUP=1,BOOKDELETE,BOOKRENT,BOOKRETURN,BOOKSEARCH,CLIENTLIST,SHOWBORROWLIST,ADMINLOGOUT,ADMINPROGRAMOUT};



	
int mainmenu();
int clientmenu();
int clientsubmenu();
int adminmenu();
int booksearchmenu();


#endif
