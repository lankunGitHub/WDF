
#include "Account.h"
#include "../Common/List.h"
#include "../Persistence/Account_Persist.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static const char ACCOUNT_KEY_NAME[]="Account";

account_t gl_CurUser;

//
void Account_Srv_InitSys(){
	if(Account_Perst_CheckAccFile())//�û��ļ�����
	{
		return;
	}
	else
	{
		printf("��ʼ����\n");
		account_t data_admin;
		printf("���������������");
		scanf("%s",data_admin.username);
		// printf("\n���������id��");
		// scanf("%d",&data_admin.id);
		long key = EntKey_Perst_GetNewKeys(ACCOUNT_KEY_NAME, 1); //��ȡ����
		if(key<=0)			
			return ;
		data_admin.id = key;



		printf("\n������������룺");
		scanf("%s",data_admin.password);
		encryption(data_admin.password);
		// printf("\n������������ͣ�");
		data_admin.type=0;

		printf("\n����������ܱ����룺");

		scanf("%lld",&data_admin.telephone);
	// 										printf("%d\n",data_admin.telephone);
	// setbuf(stdin,NULL);
	// getchar();
		// printf("����");
		// setbuf(stdin,NULL);
		// getchar();
		// fflush(stdin);

		Account_Srv_Add(&data_admin);
	}
	return;

}

//
int Account_Srv_Vertify(char usrName[], char pwd[]){
	account_t usr;
	int t;
	t=Account_Perst_SelByName(usrName,&usr);
	if(t==1)
	{
		gl_CurUser=usr;
		// printf(" type = %d\n",gl_CurUser.type);
		return 1;
	}
	// printf(" type = %d\n",gl_CurUser.type);
		
	return 0;
}
int Account_Srv_Vertify1(char usrName[], char pwd[])
{
	account_t usr;
	Account_Perst_SelByName(usrName,&usr);
	if(strcmp(usr.password,pwd)==0)
	{
		gl_CurUser=usr;
		return 1;
	}
	else
	{
		return 0;
	}	
}



//
account_node_t * Account_Srv_FindByUsrName(account_list_t list, char usrName[]) {

	account_node_t *pos;
	pos=(account_list_t)malloc(sizeof(account_node_t));
	List_ForEach(list,pos)
	{
		if(strcmp(pos->data.username,usrName)==0)
		{
			return pos;
		}
	}

	return NULL ;
}

//
int Account_Srv_Add(const account_t *data){
	int i;

	i=Account_Perst_Insert(data);

	// printf("����");
	// 	setbuf(stdin,NULL);
	// 	getchar();
		
	if(i==1){
		printf("��ӳɹ�!\n");
		return 1;
	}
	else
	{
		printf("���ʧ�ܣ�\n");
		return 0;
	}
}

//
int Account_Srv_Modify(account_t *data){
	int i;
	i=Account_Perst_Update(data);

	if(i==0)
	{
		printf("�޸�����ʧ�ܣ�");
	}
	else
	{
		printf("\n\n\n\n");
	}
}


//
inline int Account_Srv_DeleteByID(int usrID){
	int i;
	i=Account_Perst_DeleteByID(usrID);
	// printf("����");
	// 	setbuf(stdin,NULL);
	// 	getchar();
	if(i==1)
	{
		printf("ɾ���û��ɹ���");
		return 1;
	}
	else
	{
		printf("ɾ��ʧ�ܣ�");
		return 0;
	}
	

}

//
inline int Account_Srv_FetchByID(int usrID, account_t *buf){
	return 1;
}

//
int Account_Srv_FetchByName(char usrName[], account_t *buf){
	return Account_Perst_SelByName(usrName,buf);
}

//
int Account_Srv_FetchAll(account_list_t list){
	int i;
	i=Account_Perst_SelectAll(list);
	return i;
}

