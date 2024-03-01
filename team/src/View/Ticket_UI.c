#include "Ticket_UI.h"

#include "../Common/List.h"
#include "../Service/Ticket.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Service/Studio.h"

#include <stdio.h>
#include <stdlib.h>
#define SIZE 5

int Ticket_UI_MgtEntry(int schedule_id)//�����ݳ�Ʊ���� 
 {	
	 schedule_t rec;;
	 if (! Schedule_Srv_FetchByID(schedule_id,&rec)) {
		printf("���ݳ��ƻ�������!\n�� [Enter] �����ϲ�!\n");
		setbuf(stdin,NULL);
		getchar();
		return 0;
	}
	play_t rec2;
	if (!Play_Srv_FetchByID(rec.play_id, &rec2)) {
		printf("�þ�Ŀ������!\n�� [Enter] �����ϲ�!\n");
		setbuf(stdin,NULL);
		getchar();
		return 0;
	}
	
	
		printf(
				"\n==================================================================\n");
		printf(
				"*************************** �ݳ��ƻ���Ϣ ***************************\n");
		printf("%8s %8s  %8s  %8s  %8s %8s\n", "�ݳ��ƻ�ID", "��ӳ��ĿID", "�ݳ���ID",
				"��ӳ����", "��ӳʱ��","��λ��");
		printf(
				"------------------------------------------------------------------\n");
		

			printf("%8d %8d  %8d  %d/%d/%d  %d/%d/%d %8d \n",rec.id ,
					rec.play_id, rec.studio_id, rec.date.year,
					rec.date.month,rec.date.day,rec.time.hour,
					rec.time.minute,rec.time.second,rec.seat_count);
        printf(
				"******************************************************************\n");
				printf(
				"\n==================================================================\n");
		printf(
				"********************** ��Ŀ��Ϣ **********************\n");
		printf("%5s %15s   %9s  %5s  %20s  %13s\n", "ID", "��Ŀ����", "��Ʒ����",
				"ʱ��", "��ʼ->����","Ʊ��");
		printf(
				"------------------------------------------------------------------\n");
			printf("%5d %10s  %8s  %5d  %d/%d/%d->%d/%d/%d  %5d\n", rec2.id,rec2.name,rec2.area,
			rec2.duration,rec2.start_date.year,rec2.start_date.month,rec2.start_date.day,rec2.end_date.year,
			rec2.end_date.month,rec2.end_date.day,rec2.price);
        printf(
				"******************************************************************\n");
		printf(
				"[1]�����ݳ�Ʊ����|����[2]��������Ʊ ����|���� [0]�����ϲ�\n");
		printf(
				"==================================================================\n");
		int choice;
		printf("��������Ҫ���еĲ���:");
			setbuf(stdin,NULL);
			scanf("%d", &choice);
			switch(choice)
			{
				case 1:
					Ticket_Srv_GenBatch(schedule_id,rec.studio_id);
					break;
				case 2:
					printf("����");
					Ticket_Srv_DeleteBatch(schedule_id);
					Ticket_Srv_GenBatch(schedule_id,rec.studio_id);
					break;
				case 0:
					break;
				default:
					printf("��������!\n");
					break;
			}
		printf("��[ENTER]�����ϲ�");
		setbuf(stdin,NULL);
		getchar();
		system("clear");
		return 0;
}
//��ѯ�ݳ�Ʊ���� 
void Ticket_UI_Query(void) {
	ticket_list_t ticket_list;
	List_Init(ticket_list,ticket_node_t);
	Ticket_Srv_FetchAll(ticket_list);//��ȡ����Ʊ
	ticket_list_t pos=(ticket_list_t)malloc(sizeof(ticket_node_t));
	int choice,id;

	do
	{
	system("clear");
	printf("====================================================\n");
	printf("[1]��ʾ�����ݳ�Ʊ   |   [2]��ѯ�ݳ�Ʊ   |   [0]����");
	printf("\n====================================================\n");

	printf("\n\n\n");

	
	fflush(stdin);
	printf("�����룺");
	fflush(stdin);
	scanf("%d", &choice);
	fflush(stdin);
	

	switch(choice)
	{
		case 1:system("clear");
			Ticket_UI_ShowTicket(ticket_list);
			break;
		case 2:
			system("clear");
			printf("����������ҵ�Ʊ��id");
			scanf("%d",&id);
			pos=Ticket_Srv_FetchByID(id,ticket_list);
			printf(
				"\n=======================================================\n");
			printf(
				"*********************** Ʊ����Ϣ **********************\n");
			printf("%5s  %5s  %5s %5s %5s","Ʊid","�ݳ��ƻ�id","��λid","�۸�","״̬");
			printf(
				"\n-------------------------------------------------------\n");
			printf("%5d  %5d  %5d  %5d  %5d\n",pos->data.id,pos->data.schedule_id,pos->data.seat_id,pos->data.price,pos->data.status);
			printf("\n\n\n\n��ʾ��������������ء�");
			setbuf(stdin,NULL);
			getchar();
			break;
		}
	}while(choice != 0);

}
//��ʾ�ݳ�Ʊ���� 
int Ticket_UI_ShowTicket(ticket_list_t list) 
{
	Pagination_t paging;
	paging.offset = 0;
	paging.pageSize = SIZE;
	int i;
	int choice;
	Paging_Locate_FirstPage(list,paging);
	
	
	ticket_list_t p;
	ticket_list_t pos;
	int count;
	List_ForEach(list,p)
	{
		count++;
	}
	paging.totalRecords=count;

	do {
		
		printf(
				"\n==============================================================\n");
		printf(
				"*********************** Ʊ����Ϣ *****************************\n");
		printf("%5s  %5s  %5s %5s %5s","Ʊid","�ݳ��ƻ�id","��λid","�۸�","״̬");
		printf(
				"\n--------------------------------------------------------------\n");
		Paging_ViewPage_ForEach(list, paging, ticket_node_t, pos, i){
				printf("%5d  %5d  %5d  %5d  %5d\n",pos->data.id,pos->data.schedule_id,pos->data.seat_id,pos->data.price,pos->data.status);			
		}
	

		printf(
				"------- ��:%2d�� ---------------------------- ҳ�� :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        
        
        printf("\n\n\n\n"); 
        
        printf(
				"**************************************************************\n");
		printf("[0]����   |   [1]��һҳ   |   [2]��һҳ");
		printf("\n==============================================================\n");


		printf("\n\n\n\n");

		fflush(stdin);
		printf("�����룺");
		fflush(stdin);
		scanf("%d", &choice);
		fflush(stdin);

		switch(choice)
		{
			case 1:system("clear");
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(list, paging, -1, ticket_node_t);
			}
			break;
			case 2:system("clear");
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(list, paging, 1, ticket_node_t);
			}
			break;
		}
	}while(choice!=0);
	system("clear");
}
