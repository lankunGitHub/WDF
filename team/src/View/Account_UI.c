
#include "../View/Account_UI.h"
#include "../Common/List.h"
#include "../Service/Account.h"
#include <stdio.h>
#include <stdlib.h>

static const char ACCOUNT_KEY_NAME[]="Account";

//#include "curses.h"
#include <conio.h>
#define SIZE 5
#define len 100

extern account_t gl_CurUser;


//#include<termios.h>
#include<unistd.h>
#include<assert.h>
#include<string.h>

const int key = 0x86;

int change(char *p)
{
char tmp = *p;
if((tmp >= '0' && tmp <= '9' ))
{
int t = (int)tmp + 15;
tmp = (char)t;
*p = tmp;
return 0;
}
else
{
int t = (int)tmp^key;
tmp = (char)t;
*p = tmp;
}
return 0;
}
int encryption(char *str)
{
int i = 0;
while(str[i] != '\0')
{
change(&str[i]); 
i++;
}
return 0;
}
int reverse(char *p)
{
char tmp = *p;
if((tmp >= 48+15 && tmp <= 48+15+9 ))
{
int t = (int)tmp - 15;
tmp = (char)t;
*p = tmp;
return 0;
}
else
{
int t = (int)tmp^key;
tmp = (char)t;
*p = tmp;
}
return 0;


}
int deciphering(char *str)
{
int i = 0;
while(str[i] != '\0')
{
reverse(&str[i]);
i++;
}
return 0;
}











int SysLogin(){

Account_Srv_InitSys();//0

gl_CurUser.type=99999999;
char name[30],passwd[30];
account_t test;
int t,count=0;
long long tele;
int flag;
char *p;
char ch;
printf("�������û�����");
scanf("%s",name);

int cnt = 0;

while(1)
{
printf("\n����������:");
int i; 
for(i= 0;i<len;i++)
{
setbuf(stdin,NULL);
passwd[i] = getch();
if(passwd[i] == '\n')
{
passwd[i] = '\0';
break;
}
if((int)passwd[i] == 127)
{
printf("\b \b");
i = i-2;
}
else
{
printf("*");
}
if(i < 0) passwd[0] = '\0';
}

encryption(passwd);
t=Account_Srv_Vertify1(name,passwd);
Account_Perst_SelByName(name,&test);

// printf("%d\n",test.telephone);
// setbuf(stdin,NULL);
// getchar();
if(t==1)
{
printf("\n��½�ɹ���");
return 1;
}	
else
{
printf("\n����������������룡");
cnt++;
}
if(cnt==3)
{
do{
printf("\n\n\n������������Ƿ��һ����루[0]���˳� | [1]�һ����룩:");
scanf("%d",&flag);
switch(flag)
{
case 1:
printf("\n��������ܱ����룺");
scanf("%lld",&tele);
if(tele==test.telephone)
{
printf("\n�����µ����룺");
int i;
for(i= 0;i<len;i++)
{
setbuf(stdin,NULL);
passwd[i] = getch();
if(passwd[i] == '\n')
{
passwd[i] = '\0';
break;
}
if((int)passwd[i] == 127)
{
printf("\b \b");
i = i-2;
}
else
{
printf("*");
}
if(i < 0) passwd[0] = '\0';
}
encryption(test.password);
Account_Srv_Modify(&test);
gl_CurUser=test;
// printf("%d\n",gl_CurUser.telephone);
// setbuf(stdin,NULL);
// getchar();

printf("��[enter]�Զ���¼��");
setbuf(stdin,NULL);
getchar();
return;
}
else
{
printf("�ܱ���������������룡");
}

}
}while(flag != 0);
if(flag==0)
{
break;
}
}
}
// printf("%d\n",gl_CurUser.telephone);
// setbuf(stdin,NULL);
// getchar();

return 0;
}




void Account_UI_MgtEntry(){
account_list_t head;
account_node_t *pos;
head=(account_list_t)malloc(sizeof(account_node_t));
pos=(account_node_t *)malloc(sizeof(account_node_t));
int i;
char name[100];


Pagination_t paging;

List_Init(head, account_node_t);
paging.offset = 0;
paging.pageSize = SIZE;
int choice;


paging.totalRecords = Account_Srv_FetchAll(head);
Paging_Locate_FirstPage(head, paging);
system("cls");


do {

printf("\n===============================================================\n");
printf("********************** ϵͳ�û���Ϣ ***************************\n");
printf("%5s %8s %10s %10s %9s\n", "ID", "����", "�û���","����","�ܱ�����");
printf("---------------------------------------------------------------\n");


Paging_ViewPage_ForEach(head, paging, account_node_t, pos, i){
deciphering(pos->data.password);
printf("%5d %5d %7s %7s %9lld\n", pos->data.id,
pos->data.type, pos->data.username, pos->data.password,pos->data.telephone);
}

printf("-------------�ܼ�:%2d ----------- Page %2d/%2d -------------------\n",
paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
printf("***************************************************************\n");
printf("[1]��һҳ | [2]��һҳ |\n[3]���ϵͳ�û� | [4]�޸�ϵͳ�û�����/�ܱ��ֻ��� |\n[5]ɾ��ϵͳ�û� | [6]��ѯϵͳ�û�\n[0]���� |");
printf("\n===============================================================\n");

fflush(stdin);
printf("Your Choice��");
fflush(stdin);
scanf("%d", &choice);

fflush(stdin);


switch (choice) {
case 3:system("cls");
if (Account_UI_Add(head)) 
{
paging.totalRecords = Account_Srv_FetchAll(head);
Paging_Locate_LastPage(head, paging, account_node_t);
}
break;
case 4:system("clear");
printf("������Ҫ�޸ĵ��û���:");
scanf("%s", name);
if (Account_UI_Modify(head,name)) {	
paging.totalRecords = Account_Srv_FetchAll(head);
List_Paging(head, paging, account_node_t);
}
break;
case 5:system("clear");
printf("������Ҫɾ�����û�����");
scanf("%s", name);
if (Account_UI_Delete(head,name)) {	
paging.totalRecords = Account_Srv_FetchAll(head);
List_Paging(head, paging, account_node_t);
}
break;
case 6:system("clear");
printf("������Ҫ��ѯ���û�����");
scanf("%s",name);
if(Account_UI_Query(head,name))
paging.totalRecords = Account_Srv_FetchAll(head);
List_Paging(head, paging, account_node_t)
;
break;
case 1:system("clear");
if (!Pageing_IsFirstPage(paging)) {
Paging_Locate_OffsetPage(head, paging, -1, account_node_t);
}
break;
case 2:system("clear");
if (!Pageing_IsLastPage(paging)) {
Paging_Locate_OffsetPage(head, paging, 1, account_node_t);
}
break;
}
} while (choice != 0);

List_Destroy(head, account_node_t);

}


int Account_UI_Add(account_list_t list){
char name1[100];
printf("������Ҫ��ӵ��û����ƣ�");
scanf("%s",name1);
setbuf(stdin,NULL);




account_node_t *buf;
buf=(account_list_t)malloc(sizeof(account_node_t));

account_list_t flag;
flag=(account_list_t)malloc(sizeof(account_node_t));
flag=Account_Srv_FindByUsrName(list,name1);
setbuf(stdin,NULL);

char c;
char passwd[len];
char passwd2[len];
if(flag==NULL)
{

while(1)
{
printf("\n����������:");
int i;
for(i= 0;i<len;i++)
{

c= getch();

if(c=='\r'||(int)c==13)
{
	setbuf(stdin,NULL);
	
	passwd[i]='\0';
	break;
}
else if(c == '\b'||(int)c == 127){
	if(i>0)
	{
		i--;
		printf("\b \b");
		passwd[i] = '\0';
		continue;}
	}
else{
	printf("*");
	passwd[i] = c;
}
passwd[i]=='\0';

}
printf("\n���ٴ���������:");
setbuf(stdin,NULL);
for(i= 0;i<len;i++)
{

c = getch();
if(c=='\r'||(int)c==13)
{
	passwd2[i]='\0';
	break;
}
else if(c == '\b'||(int)c == 127){
	if(i>0)
	{
		i--;
		printf("\b \b");
		passwd2[i] = '\0';
		continue;}
	}
else{
	printf("*");
	passwd2[i] = c;
}

}

if(strcmp(passwd,passwd2) == 0)
{

break;
}
else
{
printf("\n�������벻һ��!"); 
}

}


encryption(passwd);
strcpy(buf->data.password,passwd);

long key = EntKey_Perst_GetNewKeys(ACCOUNT_KEY_NAME, 1); //��ȡ����
if(key<=0)	
return 0;
buf->data.id = key;


printf("\n�����û����ͣ�1,2,9����");
scanf("%d",&buf->data.type);

printf("�������ܱ��ֻ��ţ�");
scanf("%lld",&buf->data.telephone);


strcpy(buf->data.username,name1);



Account_Srv_Add(&buf->data);


List_AddTail(list,buf);


return 1;
}

else
{
printf("�����û��Ѵ��ڣ�");

return 0;
}

}
int Account_UI_Modify(account_list_t list,char usrName[]){
account_node_t *flag;
flag=(account_list_t)malloc(sizeof(account_node_t));
flag=Account_Srv_FindByUsrName(list,usrName);

char passwd[len];
char passwd2[len];
if(flag==NULL)
{
printf("���û������ڣ�");
return;
}
else
{
while(1)
{
char passwd[len];
char passwd2[len];
printf("\n����������:");
int i;
for(i= 0;i<len;i++)
{
	passwd[i] = getch();
	if(passwd[i] == '\r'||passwd[i] == '\n'||(int)passwd[i]==13)
		{	
		passwd[i] ='\0';
		break;
		}
	if((int)passwd[i] == 127&&passwd[i]!='r'&&passwd[i] == '\n'&&passwd[i] != '\0'&&(int)passwd[i]!=13)
		{
		printf("\b \b");
		i = i-2;
		}
	else
		{
		printf("*");
		}
	if(i < 0) passwd[0] = '\0';
	if(passwd[i] == '\r'||passwd[i] == '\n'||passwd[i] == '\0'||(int)passwd[i]==13)
	break;
}
printf("\n���ٴ���������:");

for(i= 0;i<len;i++)
{
setbuf(stdin,NULL);
passwd2[i] = getch();
if(passwd2[i] == '\n')
{
passwd2[i] = '\0';
break;
}
if((int)passwd2[i] == 127)
{
printf("\b \b");
i = i-2;
}
else
{
printf("*");
}
if(i < 0) passwd2[0] = '\0';
}
if(strcmp(passwd,passwd2) == 0)
{

break;
}
else
{
printf("\n�������벻һ��!"); 
}

}

encryption(passwd);
strcpy(flag->data.password,passwd);

long long tele;
int t;
while(t!=1)
{
printf("\n�Ƿ��޸�λ�ܱ����루[0]���޸� | [1]�޸ģ���");
scanf("%lld",&t);
if(t==1)
{
printf("�����µ��ܱ����룺");
scanf("%lld",&tele);
flag->data.telephone=tele;
}
else if(t==0)
{
break;
}

else
{
printf("��������������룡");
}
}
Account_Srv_Modify(&(flag->data));

}


return 1;

}


int Account_UI_Delete(account_list_t list,char usrName[]){
account_node_t *flag;
flag=(account_list_t)malloc(sizeof(account_node_t));
flag=Account_Srv_FindByUsrName(list,usrName);

if(flag==NULL)
{
printf("���û������ڣ�");

return;
}
else
{

Account_Srv_DeleteByID(flag->data.id);

}



return 1;

}


int Account_UI_Query(account_list_t list,char usrName[]){
account_node_t *flag;
flag=(account_list_t)malloc(sizeof(account_node_t));
flag=Account_Srv_FindByUsrName(list,usrName);
deciphering(flag->data.password);
if(flag==NULL)
{
printf("���û������ڣ�");
return 0;
}
else
{
printf("=============================\n");
printf("id-------------%d\n",flag->data.id);
printf("�û���----------%s\n",flag->data.username);
printf("����------------%s\n",flag->data.password);
printf("�û�����---------%d\n",flag->data.type);
printf("\n\n\n\n\n\n\n\n\n");

}
return 1;

}
