#include <string.h>
#include <stdio.h>
#include "SalesAnalysis.h"
#include "Sale.h"
#include "Ticket.h"
#include "Play.h"
#include "Schedule.h"
#include "../Common/List.h"
int SalesAnalysis_Srv_StaticSale(salesanalysis_list_t list)//�����ĿƱ����Ϣ���� (����Ҫ��Ŀ���ݺ�Ʊ�����ݣ����ݾ�Ŀ���Ʊ����������Ŀ����ȡƱ����Ϣ)
//��Ҫ�����Ŀ�ĺ�������ȡƱ���ĺ���  
{
	int cnt = 0;//��ҳ�� 
	assert(list!=NULL);
	play_list_t playlist;//��Ŀ��ͷβ�ڵ� 
	play_node_t *pos;
	int sold;//�洢������ЧƱ��
	salesanalysis_list_t p;
	List_Free(list,salesanalysis_node_t);//�ͷ����� 
	List_Init(playlist,play_node_t);//��ʼ������ 
	int playcount = Play_Srv_FetchAll(playlist);//�������о�Ŀ ������������������������������� 
	List_ForEach(playlist,pos)//��ʼ������� 
	{
		p  =   (salesanalysis_list_t)malloc(sizeof(salesanalysis_node_t));
		strcpy(p->data.area,pos->data.area);
		p->data.duration = pos->data.duration;
		p->data.end_date = pos->data.end_date;
		strcpy(p->data.name,pos->data.name);
		p->data.play_id = pos->data.id;
		p->data.price = pos->data.price;
		p->data.start_date = pos->data.start_date;
		
		p->data.sales = Schedule_Srv_StatRevByPlay(pos->data.id,&sold);//Ʊ��,���ݾ�ĿID��ȡƱ�� !!!!!!!!!!!!!!!!!!!!!Schedule_Srv_StatRevByPlay*****����� 
		p->data.totaltickets = sold;//�������� 

		

		List_AddTail(list,p);
		// printf("��Ŀid :%d\n",pos->data.id);
		cnt++;
	}
	return cnt;

}
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list)
 { 
	salesanalysis_list_t p,listleft;    
  	if(list == NULL) return ;   
    list->prev->next = NULL;//ѭ���Ͽ�     
	listleft =  list->next;//listleftָ���һ�����ݽڵ� 
	list->next = list->prev = list;//�������������Ϊ��  
	while(listleft != NULL)    
	{   
		       p = listleft;     
			 listleft = listleft->next;       
    SalesAnalysis_Srv_AddToSoftedList(list,p); //�������򣡣���������������������� 
	}     
	return ; 
} 
void SalesAnalysis_Srv_AddToSoftedList(salesanalysis_list_t list, salesanalysis_node_t *p)
{
   salesanalysis_node_t *cur;   
   if(list == NULL)  
    {         List_AddTail(list,p);     }     //β�巨 
	  
   else   
  	{        
	   cur = list->next;       
	     while(cur != list)      
		    {            
				 if(p->data.sales > cur->data.sales) break;  //pƱ������curƱ�� 
				            cur = cur->next;      
		   }      
		      List_InsertBefore(cur,p);    //��p����cur֮ǰ 
	}   
	  return ;
}
//����Ϊ˼��ʱ�ľ��� 
/*
void Seat_Srv_SortSeatList(seat_list_t list) {
       seat_list_t listLeft,p;
       if(list == NULL) return ;
       list->prev->next = NULL;//�Ͽ�ѭ������
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
       seat_list_t p  = list->next;//����������
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

