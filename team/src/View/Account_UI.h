#ifndef ACCOUNT_UI_H_
#define ACCOUNT_UI_H_

#include "../Common/List.h"
#include "../Service/Account.h"

static const int ACCOUNT_PAGE_SIZE = 3;

int encryption(char *str);
int change(char *p);
int SysLogin();
int reverse(char *p);
int deciphering(char *str);
//
void Account_UI_MgtEntry();

//
int  Account_UI_Add(account_list_t list);

//
int Account_UI_Modify(account_list_t list,char usrName[]);

//
int Account_UI_Delete(account_list_t list,char usrName[]);

//
int Account_UI_Query(account_list_t list,char usrName[]);

//int getch();


#endif /* ACCOUNT_UI_H_ */

