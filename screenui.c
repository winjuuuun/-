#include "common.h"
#include "client.h"
#include "book.h"
#include "borrow.h"
#include "admin.h"
#include "fileio.h"
#include "screenui.h"




int mainmenu(){
	int cho;
	printf(">> 도서관 서비스 << \n");
	printf("1.회원가입	2.로그인 3.프로그램 종료\n");
	printf("번호를 선택하세요:");
	scanf("%d",&cho); 
	return cho;
}
int adminmenu(){
	int cho;
	printf(">> 관리자 메뉴 <<\n");
	printf("1. 도서 등록\n");
	printf("2.도서 삭제\n");
	printf("3.도서 대여\n");
	printf("4.도서 반납\n");
	printf("5.도서 검색\n");
	printf("6.회원목록\n");
	printf("7.대여목록보기\n");
	printf("8.로그아웃\n");
	printf("9.프로그램 종료\n"); 
	printf("번호를 선택하세요:"); 
	scanf("%d",&cho);
	return cho;
}
int clientsubmenu(){
	int cho;
	printf("1.이름 검색\n");
	printf("2.학번 검색\n");
	printf("3.전체 검색\n");
	printf("번호를 선택하세요:"); 
	scanf("%d",&cho);
	return cho;
}
int clientmenu(){
	int cho;
	printf(">> 회원 메뉴 << \n");
	printf("1.도서 검색\n");
	printf("2.대여 목록\n");
	printf("3.개인정보수정\n");
	printf("4.회원탈퇴\n");
	printf("5.로그아웃\n");
	printf("6.프로그램 종료\n");
	printf("번호를 선택하세요:"); 
	scanf("%d",&cho);
	return cho;
}
int booksearchmenu(){
	int cho;
	printf(">> 도서 검색 <<\n");
	printf("1. 도서명 검색\n");
	printf("2.출판사명 검색\n");
	printf("3.ISBN 검색\n");
	printf("4.저자명 검색\n");
	printf("5.전체 검색\n");
	printf("6.나가기\n");
	printf("번호를 선택하세요:"); 
	scanf("%d",&cho);
	return cho;
}
	 

