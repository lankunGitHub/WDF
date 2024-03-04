#include "Ticket.h"
#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Persistence/Ticket_Persist.h"
#include "../Persistence/Play_Persist.h"
#include "../Persistence/Schedule_Persist.h"
#include "./Sale.h"
#include <stdio.h>
#include <stdlib.h>



int Ticket_Srv_StatRevSchID(int schedule_id,int *soldCount)//�����ݳ��ƻ�ID��ȡƱ��
{
	int value = 0;//���Ʊ��
	ticket_list_t list;
	ticket_node_t *p;
	int Sale_bool;
	sale_t sale;//Ʊ 
	List_Init(list,ticket_node_t);//��ʼ������ 
	*soldCount = 0;//��Ч��Ʊ������
	*soldCount = Ticket_Srv_FetchBySchID(list,schedule_id);//�����ݳ��ƻ�ID��ȡƱ������ 
	List_ForEach(list,p)//���� 
	{
		Sale_bool = Sale_Srv_FetchByticket(p->data.id,&sale);//����ƱID��ȡ���ۼ�¼ 
		//sale.type = 1;
		if(sale.type == 1 && p->data.status == 1)//ȷ��Ϊ��Ʊ״̬����ȷ��Ϊ����
		{
			*soldCount++;
			value +=  p->data.price;
		}
	}

	List_Destroy(list,ticket_node_t);//�������� 
	return value;
}

int Ticket_Srv_FetchBySchID(ticket_list_t list, int schedule_id)
{
	return Ticket_Perst_SelectBySchID(list,schedule_id);////�����ݳ��ƻ�ID����Ʊ������
}

//�����ݳ�Ʊ���� 
int Ticket_Srv_GenBatch(int schedule_id, int studio_id)
{
	seat_list_t list;
	list = (seat_node_t*)malloc(sizeof(seat_node_t));
	List_Init(list,seat_node_t);//��ʼ������ 
	Seat_Srv_FetchValidByRoomID(list,studio_id);
	  int cnt = Ticket_Perst_Insert(schedule_id,list);
	if(cnt > 0)
	{
		printf("�ɹ�����Ʊ!\n");
	}
	else
	{
		printf("����Ʊʧ��!\n");
	}
	
	return cnt;
}

//�����ݳ��ƻ�IDɾ���ݳ�Ʊ���� 
int Ticket_Srv_DeleteBatch(int schedule_id) 
{
	return Ticket_Perst_Rem(schedule_id);//�����ݳ��ƻ�IDȥ���ݳ�Ʊ 
}

//��ȡȫ���ݳ�Ʊ���� 
int Ticket_Srv_FetchAll(ticket_list_t ticket_list)
{
	return Ticket_Perst_SelectAll(ticket_list);//����ȫ���ݳ�Ʊ 
}

//����ID��ȡ�ݳ�Ʊ���� 
ticket_list_t Ticket_Srv_FetchByID (int id,ticket_list_t buf)//id ��ʲôid
{
	ticket_list_t p;
	List_ForEach(buf,p)
	{
		if(p->data.seat_id == id)
		return p;
	}
	return NULL;
	
}

ticket_list_t Ticket_Srv_FetchByID (int id,ticket_list_t buf)//id ��ʲôid
{
	ticket_list_t p;
	List_ForEach(buf,p)
	{
		if(p->data.seat_id == id)
		return p;
	}
	return NULL;
	
}
int Ticket_Srv_Modify (const ticket_t *data){

	return Ticket_Perst_Update(data);
}


//??????????ID??????????
int Ticket_Srv_FetchBySchID(ticket_list_t list, int schedule_id)
{
	return Ticket_Perst_SelectBySchID(list,schedule_id);

}


//????ID????
ticket_node_t * Ticket_Srv_FetchBySeatID (ticket_list_t list, int seat_id)
{
	ticket_node_t* p;
	List_ForEach(list,p)
	{
			if(p->data.seat_id == seat_id) return p;
	}
	return NULL;
}

int Ticket_Srv_FetchBySchID(ticket_list_t list, int schedule_id)
{
	return Ticket_Perst_SelectBySchID(list,schedule_id);

}


