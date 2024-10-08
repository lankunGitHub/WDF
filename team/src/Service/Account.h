
#ifndef ACCOUNT_H_
#define ACCOUNT_H_

//
typedef enum {
	USR_ANOMY = 0, //
	USR_CLERK =1, //
	USR_MANG = 2, //
	USR_ADMIN = 9 //
} account_type_t;

//
typedef struct {
	int  id;//
	account_type_t type;//
	char username[30];//
	char password[30];//
	long long  telephone;
} account_t;

//
typedef struct account_node {
	account_t data;
	struct account_node *next, *prev;
} account_node_t, *account_list_t;


//
void Account_Srv_InitSys();

//
int Account_Srv_Verify(char usrName[], char pwd[]);

int Account_Srv_Add(const account_t *data);

int Account_Srv_Modify(account_t *data);

int Account_Srv_DeleteByID(int usrID);

int Account_Srv_FetchByID(int usrID, account_t *buf);

int Account_Srv_FetchByName(char usrName[], account_t *buf);

//
int Account_Srv_FetchAll(account_list_t list);

//
account_node_t * Account_Srv_FindByUsrName(account_list_t list, char usrName[]);

int Account_Srv_Vertify1(char usrName[], char pwd[]);


#endif 
 
