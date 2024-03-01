#ifndef SALESANALYSIS_H_
#define SALESANALYSIS_H_
#include "Sale.h"
#include "Ticket.h"
#include "Play.h"
#include "Schedule.h"
#include "../Common/List.h"
/*ͳ��Ʊ�߼��ӿ�*/ 


//��Ŀ���ݽṹ 

typedef struct {
	int play_id; 	//��Ŀid
	char name[31]; 	//��Ŀ���� 
	char area[9]; 	//��Ŀ���� 
	int duration; 	//��Ŀ����ʱ�� 
	long totaltickets; //��Ŀ�������� 
	long sales; 	//��ĿƱ��(���۶�ͳ��) 
	int price; 		//��ĿƱ�� 
	
	ttms_date_t start_date; 	//��Ŀ��ӳʱ�� 
	ttms_date_t end_date; 	//��Ŀ��ӳʱ�� 
} salesanalysis_t;


//˫������
typedef struct salesanalysis_node {
	salesanalysis_t data;
	struct salesanalysis_node *next, *prev;
} salesanalysis_node_t, *salesanalysis_list_t;
//��ȡ��ĿƱ����Ϣ 
int SalesAnalysis_Srv_StaticSale(salesanalysis_list_t list);//�����ܼ�¼�� ,�������� 

//���ݾ�ĿID��ȡƱ�� ������ 
//int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount);

//�����ݳ��ƻ�ID��ȡƱ��
//int Ticket_Srv_StatRevBySchID(int schedule_id, int *soldCount);

//�����ݳ��ƻ�ID��ȡƱ������ 
//int Ticket_Srv_FetchBySchID(ticket_list_t list, int schedule_id);

//��ĿƱ������() 
void SalesAnalysis_Srv_SortBySale(salesanalysis_list_t list);

void SalesAnalysis_Srv_AddToSoftedList(salesanalysis_list_t list, salesanalysis_node_t *node);

//��ȡȫ����Ŀ
//Play_Srv_FetchAll

//����ƱID��ȡ���ۼ�¼
//int Sale_Srv_FetchByTicketID(int ticket_id, sale_t *sale);



#endif
