#ifndef SALESANALYSIS_H_
#define SALESANALYSIS_H_
#include "Sale.h"
#include "Ticket.h"
#include "Play.h"
#include "Schedule.h"
#include "../Common/List.h"
/*统计票逻辑接口*/ 


//剧目数据结构 

typedef struct {
	int play_id; 	//剧目id
	char name[31]; 	//剧目名称 
	char area[9]; 	//剧目区域 
	int duration; 	//剧目播放时长 
	long totaltickets; //剧目上座数量 
	long sales; 	//剧目票房(销售额统计) 
	int price; 		//剧目票价 
	
	ttms_date_t start_date; 	//剧目上映时间 
	ttms_date_t end_date; 	//剧目下映时间 
} salesanalysis_t;


//双向链表
typedef struct salesanalysis_node {
	salesanalysis_t data;
	struct salesanalysis_node *next, *prev;
} salesanalysis_node_t, *salesanalysis_list_t;
//获取剧目票房信息 
int SalesAnalysis_Srv_StaticSale(salesanalysis_list_t list);//返回总记录数 ,载入数据 

//根据剧目ID获取票房 及数量 
//int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount);

//根据演出计划ID获取票房
//int Ticket_Srv_StatRevBySchID(int schedule_id, int *soldCount);

//根据演出计划ID获取票房数据 
//int Ticket_Srv_FetchBySchID(ticket_list_t list, int schedule_id);

//剧目票房排行() 
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list);

void SalesAnalysis_Srv_AddToSoftedList(salesanalysis_list_t list, salesanalysis_node_t *node);

//获取全部剧目
//Play_Srv_FetchAll

//根据票ID获取销售记录
//int Sale_Srv_FetchByTicketID(int ticket_id, sale_t *sale);



#endif
