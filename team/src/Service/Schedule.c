#include "Schedule.h"
#include "../Common/List.h"
#include "../Persistence/Schedule_Persist.h"
#include "Ticket.h"
#include <stdio.h>
#include "../Service/Sale.h"


int Schedule_Srv_Add(schedule_t *data)//������ݳ��ƻ����� 
 {
	return Schedule_Perst_Insert(data);
}


int Schedule_Srv_Modify(schedule_t *data)//�޸��ݳ��ƻ����� 
 {
	return Schedule_Perst_Update(data);
}

 int Schedule_Srv_DeleteByID(int ID)//����IDɾ���ݳ��ƻ����� 
{
	return Schedule_Perst_RemByID(ID);
}

 int Schedule_Srv_FetchByID(int id,schedule_t *buf)//����ID��ȡ�ݳ��ƻ����� 
{
	return Schedule_Perst_SelectByID(id,buf);//����ID�����ݳ��ƻ� 
}


int Schedule_Srv_FetchAll(schedule_list_t list)//��ȡȫ���ݳ��ƻ����� 
{
        return Schedule_Perst_SelectAll(list);//����ȫ���ݳ��ƻ� 
}

int Schedule_Srv_FetchByPlay(schedule_list_t list,int play_id)//���ݾ�ĿID��ȡ�ݳ��ƻ����� 
{
	return Schedule_Perst_SelectByPlay(list,play_id);//���ݾ�ĿID�����ݳ��ƻ� 

}
 
int Schedule_Srv_StatRevByPlay(int play_id, int *soldCount)//�ݾ�ĿID��ȡƱ��
{
	
	int value = 0;//�洢Ʊ��
	int sold = 0; //�洢��Ч��Ʊ����
	
	schedule_list_t list;//˫������ 
	schedule_node_t *p;
	*soldCount = 0;//��Ʊ������ 
	List_Init(list,schedule_node_t);//���ݳ��ƻ�����list
	int play_count = Schedule_Perst_SelectByPlay(list,play_id);//���ݾ�Ŀid�����ݳ��ƻ�!!!!!!!!!!!!!!!!!!!!!!!!!!����ɵ������� ?????????????????????????????????
	List_ForEach(list,p)//���� 
	{
		value += Ticket_Srv_StatRevSchID(p->data.id,&sold);//�����ݳ��ƻ�ID��ȡƱ��!!!!!!!!δ��� 
		*soldCount = *soldCount+sold;
	}
	List_Destroy(list,schedule_node_t);//��������
	return value;//����ֵΪƱ�� 


}
