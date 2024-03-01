#include "Play.h"
#include "../Common/List.h"
#include "../Persistence/Play_Persist.h"
#include <string.h>
//添加新剧目服务 
int Play_Srv_Add( play_t *data)
{
	return Play_Perst_Insert(data);//存储新剧目 
}
//修改剧目服务 
 inline int Play_Srv_Modify( play_t *data) {
 	
 return Play_Perst_Update(data);
 }                              //更新剧目 


 int Play_Srv_DeleteByID(int ID)
{
	return Play_Perst_RemByID(ID);//根据ID去除剧目 
}

//根据ID获取剧目服务
int Play_Srv_FetchByID(int id,play_t *buf)
{
	return Play_Perst_SelectByID(id,buf);//根据ID载入剧目 
}

//载入所有剧目 
int Play_Srv_FetchAll(play_list_t list)
{
	return Play_Perst_SelectAll(list);//从文件中载入所有剧目 
}


//根据名称获取剧目服务 
int Play_Srv_FetchByName(play_list_t list, char condt[])
{
	return Play_Perst_SelectByName(list, condt);;//根据名称载入剧目 

}


int Play_Srv_FilterByName(play_list_t list, char filter[]);

