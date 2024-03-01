#include <string.h>
#include <stdio.h>
#include "SalesAnalysis.h"
#include "Sale.h"
#include "Ticket.h"
#include "Play.h"
#include "Schedule.h"
#include "../Common/List.h"
int SalesAnalysis_Srv_StaticSale(salesanalysis_list_t list)//载入剧目票房信息数据 (故需要剧目内容和票房内容，根据剧目获得票房，遍历剧目来获取票房信息)
//需要载入剧目的函数，获取票房的函数  
{
	int cnt = 0;//总页数 
	assert(list!=NULL);
	play_list_t playlist;//剧目的头尾节点 
	play_node_t *pos;
	int sold;//存储已售有效票数
	salesanalysis_list_t p;
	List_Free(list,salesanalysis_node_t);//释放链表 
	List_Init(playlist,play_node_t);//初始化链表 
	int playcount = Play_Srv_FetchAll(playlist);//载入所有剧目 ！！！！！！！！！！！！！已完成 
	List_ForEach(playlist,pos)//开始载入遍历 
	{
		p  =   (salesanalysis_list_t)malloc(sizeof(salesanalysis_node_t));
		strcpy(p->data.area,pos->data.area);
		p->data.duration = pos->data.duration;
		p->data.end_date = pos->data.end_date;
		strcpy(p->data.name,pos->data.name);
		p->data.play_id = pos->data.id;
		p->data.price = pos->data.price;
		p->data.start_date = pos->data.start_date;
		
		p->data.sales = Schedule_Srv_StatRevByPlay(pos->data.id,&sold);//票房,根据剧目ID获取票房 !!!!!!!!!!!!!!!!!!!!!Schedule_Srv_StatRevByPlay*****已完成 
		p->data.totaltickets = sold;//上座数量 

		

		List_AddTail(list,p);
		// printf("剧目id :%d\n",pos->data.id);
		cnt++;
	}
	return cnt;

}
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list)
 { 
	salesanalysis_list_t p,listleft;    
  	if(list == NULL) return ;   
    list->prev->next = NULL;//循环断开     
	listleft =  list->next;//listleft指向第一个数据节点 
	list->next = list->prev = list;//将ｌｉｓｔ链表置为空  
	while(listleft != NULL)    
	{   
		       p = listleft;     
			 listleft = listleft->next;       
    SalesAnalysis_Srv_AddToSoftedList(list,p); //依次排序！！！！！！！！！！已完成 
	}     
	return ; 
} 
void SalesAnalysis_Srv_AddToSoftedList(salesanalysis_list_t list, salesanalysis_node_t *p)
{
   salesanalysis_node_t *cur;   
   if(list == NULL)  
    {         List_AddTail(list,p);     }     //尾插法 
	  
   else   
  	{        
	   cur = list->next;       
	     while(cur != list)      
		    {            
				 if(p->data.sales > cur->data.sales) break;  //p票房大于cur票房 
				            cur = cur->next;      
		   }      
		      List_InsertBefore(cur,p);    //将p插在cur之前 
	}   
	  return ;
}
//以下为思索时的举例 
/*
void Seat_Srv_SortSeatList(seat_list_t list) {
       seat_list_t listLeft,p;
       if(list == NULL) return ;
       list->prev->next = NULL;//断开循环链表
       listLeft = list->next;
       list->next = list->prev = list;
       if(listLeft == NULL) return ;
       else
       {
              p = listLeft;
              listLeft = listLeft->next;
              Seat_Srv_AddToSoftedList(list,p);
       }
       return ;
}
void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node) {
       seat_list_t p  = list->next;//可能有问题
       if(list == NULL) 
       {
              List_AddTail(list,node);
       }
       else
       {
              while(p!= list && (p->data.row < node->data.row || (p->data.row == node->data.row && p->data.column < node->data.column)))
              {
                     p = p->next;
              }
              List_AddHead(p,node);
       }
       return ;
}*/

