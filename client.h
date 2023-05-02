#ifndef __CLIENT_H
#define __CLIENT_H
CLIENT* onesign();
void signup();
int login();
int admin_menu(char*,char*);
int clientservice(char*,char*);
void admin_logout(char*,char*);
void client_logout(char*,char*);
void name_search();
void student_num_search();
void everything_search();
int checkclient_borrow_exist(char *);
void client_rentlist(char*);
void client_info_fix(char*);
void deleteclient(char *);
void signout(char *,char *);
#endif
