#include "Schedule.h"
#include "../Common/List.h"
#include "../Persistence/Schedule_Persist.h"
#include "Ticket.h"
#include <stdio.h>
#include "../Service/Sale.h"


int Schedule_Srv_Add(schedule_t *data)//添加新演出计划服务 
 {
	return Schedule_Perst_Insert(data);
}


int Schedule_Srv_Modify(schedule_t *data)//修改演出计划服务 
 {
	return Schedule_Perst_Update(data);
}

 int Schedule_Srv_DeleteByID(int ID)//根据ID删除演出计划服务 
{
	return Schedule_Perst_RemByID(ID);
}

 int Schedule_Srv_FetchByID(int id,schedule_t *buf)//根据ID获取演出计划服务 
{
	return Schedule_Perst_SelectByID(id,buf);//根据ID载入演出计划 
}


int Schedule_Srv_FetchAll(schedule_list_t list)//获取全部演出计划服务 
{
        return Schedule_Perst_SelectAll(list);//载入全部演出计划 
}

int Schedule_Srv_FetchByPlay(schedule_list_t list,int play_id)//根据剧目ID获取演出计划服务 
{
	return Schedule_Perst_SelectByPlay(list,play_id);//根据剧目ID载入演出计划 

}
 
int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount)//据剧目ID获取票房
{
	
	int value = 0;//存储票房
	int sold = 0; //存储有效售票数量
	
	schedule_list_t list;//双向链表 
	schedule_node_t *p;
	*soldCount = 0;//售票总数量 
	List_Init(list,schedule_node_t);//建演出计划链表list
	int play_count = Schedule_Perst_SelectByPlay(list,play_id);//根据剧目id载入演出计划!!!!!!!!!!!!!!!!!!!!!!!!!!已完成但有疑问 ?????????????????????????????????
	List_ForEach(list,p)//遍历 
	{
		value += Ticket_Srv_StatRevSchID(p->data.id,&sold);//根据演出计划ID获取票房!!!!!!!!未完成 
		*soldCount = *soldCount+sold;
	}
	List_Destroy(list,schedule_node_t);//销毁链表
	return value;//返回值为票房 


}
