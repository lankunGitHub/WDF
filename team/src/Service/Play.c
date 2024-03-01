#include "Play.h"
#include "../Common/List.h"
#include "../Persistence/Play_Persist.h"
#include <string.h>
//����¾�Ŀ���� 
int Play_Srv_Add( play_t *data)
{
	return Play_Perst_Insert(data);//�洢�¾�Ŀ 
}
//�޸ľ�Ŀ���� 
 inline int Play_Srv_Modify( play_t *data) {
 	
 return Play_Perst_Update(data);
 }                              //���¾�Ŀ 


 int Play_Srv_DeleteByID(int ID)
{
	return Play_Perst_RemByID(ID);//����IDȥ����Ŀ 
}

//����ID��ȡ��Ŀ����
int Play_Srv_FetchByID(int id,play_t *buf)
{
	return Play_Perst_SelectByID(id,buf);//����ID�����Ŀ 
}

//�������о�Ŀ 
int Play_Srv_FetchAll(play_list_t list)
{
	return Play_Perst_SelectAll(list);//���ļ����������о�Ŀ 
}


//�������ƻ�ȡ��Ŀ���� 
int Play_Srv_FetchByName(play_list_t list, char condt[])
{
	return Play_Perst_SelectByName(list, condt);;//�������������Ŀ 

}


int Play_Srv_FilterByName(play_list_t list, char filter[]);

