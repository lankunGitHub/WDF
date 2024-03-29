#include "Schedule_UI.h"
#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Service/Studio.h"
#include "../Service/Seat.h"
#include <stdio.h>
#include <stdlib.h>
#include "./Ticket_UI.h"
int Schedule_UI_MgtEnt()
{
    int i, id;
	int choice;

	schedule_list_t head;
	schedule_node_t *pos;
	Pagination_t paging;

	List_Init(head, schedule_node_t);
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	paging.totalRecords = Schedule_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
	do {
        //????????????????
		printf(
				"\n==================================================================\n");
		printf(
				"************************** �ݳ��ƻ���Ϣ ************************\n");
		printf("%8s %8s  %8s  %8s    %8s      %8s\n", "�ݳ��ƻ�ID", "��ӳ��ĿID", "�ݳ���ID",
				"��ӳ����", "��ӳʱ��","��λ��");
		printf(
				"------------------------------------------------------------------\n");
		
		Paging_ViewPage_ForEach(head, paging, schedule_node_t, pos, i){
			printf("%6d   %8d  %8d      %d/%d/%d    %d:%d:%d %8d \n", pos->data.id,
					pos->data.play_id, pos->data.studio_id, pos->data.date.year,
					pos->data.date.month,pos->data.date.day,pos->data.time.hour,
					pos->data.time.minute,pos->data.time.second,pos->data.seat_count);
		}

		printf(
				"--------------- ��:%2dҳ ----------------------- ҳ�� :%2d/%2d -----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        
        
        printf("\n\n\n\n"); 
        
        
        printf(
				"******************************************************************\n");
		printf(
				"[1]��һҳ         |   [2]��һҳ         |   [3]�����ݳ��ƻ�   |\n[4]ɾ���ݳ��ƻ�   |   [5]�޸��ݳ��ƻ�   |   [6]�����ݳ�Ʊ     |\n[0]�����ϲ�       |");
		printf(
				"\n\n\n\n==================================================================\n");
        printf("��������Ҫ���еĲ���:");
		fflush(stdin);
        setbuf(stdin,NULL);
		scanf("%d", &choice);
		setbuf(stdin,NULL);
		fflush(stdin);


     
		switch (choice) {
		case 3:
            system("clear");
			printf("������Ҫ���ɵ��ݳ��ƻ��ľ�ĿID:");
			scanf("%d", &id);
			if (Schedule_UI_Add(id)) 
			{
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, schedule_node_t);
			}
			break;
		case 4:
            system("clear");
			printf("������Ҫɾ�����ݳ��ƻ�ID:");
			scanf("%d", &id);
			if (Schedule_UI_Delete(id)) {	
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				List_Paging(head, paging, schedule_node_t);
			}
			break;
		case 5:
            system("clear");
			printf("������Ҫ�޸ĵ��ݳ��ƻ�ID");
			scanf("%d", &id);
			if (Schedule_UI_Modify(id)) {	
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				List_Paging(head, paging, schedule_node_t);
			}
			break;
		case 6:
            system("clear");
			int id;
			printf("��ѡ��Ҫ�����ĸ��ݳ��ƻ����ݳ�Ʊ(ID):");
			scanf("%d",&id);
			Ticket_UI_MgtEntry(id);
			break;
		case 1:
            system("clear");
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
			}
			break;
		case 2:
            system("clear");
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
			}
			break;
		}
	} while (choice != 0);
	//??????????
    system("clear");
	List_Destroy(head, schedule_node_t);

    return 0;
}

void Schedule_UI_ListAll(void) 
{
	int i, id;
	int choice;
	char name[64];
	schedule_list_t head;
	schedule_node_t *pos;
	Pagination_t paging;

	List_Init(head, schedule_node_t);
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	paging.totalRecords = Schedule_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
	do {
        //????????????????
		printf(
				"\n==========================================================\n");
		printf(
				"********************** �ݳ��ƻ���Ϣ **********************\n");
		printf("%8s %8s  %8s  %8s  %8s %8s\n", "�ݳ��ƻ�ID", "��ӳ��ĿID", "�ݳ���ID",
				"��ӳ����", "��ӳʱ��","��λ��");
		printf(
				"----------------------------------------------------------\n");
		
		Paging_ViewPage_ForEach(head, paging, schedule_node_t, pos, i){
			printf("%8d %8d  %8d  %d/%d/%d  %d/%d/%d %8d \n", pos->data.id,
					pos->data.play_id, pos->data.studio_id, pos->data.date.year,
					pos->data.date.month,pos->data.date.day,pos->data.time.hour,
					pos->data.time.minute,pos->data.time.second,pos->data.seat_count);
		}

		printf(
				"------- ��:%2dҳ ------------------------- ҳ�� :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        
        
        printf("\n\n\n\n"); 
        
        
        printf(
				"**********************************************************\n");
		printf(
				"[1]��һҳ    |   [2]��һҳ   |   [3] ��������ɸѡ�ݳ��ƻ�\n[0]�����ϲ�  |");
		printf(
				"\n\n\n\n==========================================================\n");
        printf("��������Ҫ���еĲ���:");
		fflush(stdin);
        setbuf(stdin,NULL);
		scanf("%d", &choice);
		setbuf(stdin,NULL);
		fflush(stdin);


     
		switch (choice) {
		case 3:
			
            system("clear");
			printf("������Ҫ��ѯ�ľ�Ŀ����:");
			scanf("%s", name);
			if (Schedule_UI_Query(name)) 
			{
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, schedule_node_t);
			}
			break;
		
		case 1:
            system("clear");
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, schedule_node_t);
			}
			break;
		case 2:
            system("clear");
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, schedule_node_t);
			}
			break;
		}
	} while (choice != 0);
    system("clear");
	List_Destroy(head, schedule_node_t);

    return 0;
}

int Schedule_UI_Add(int play_id)
 {
	 play_t buf;
	if( !Play_Srv_FetchByID(play_id,&buf ) )
	{
		printf("�þ�Ŀ������!\n");
		printf("��[ENTER]�����ϲ�\n");
		setbuf(stdin,NULL);
		getchar();
		return 0;
	}


	schedule_t rec;
	int newRecCount = 0;
	char choice;

	do {
		system("clear");
		printf("\n=======================================================\n");
		printf("****************  �������ݳ��ƻ�  ****************\n");
		printf("-------------------------------------------------------\n");
		
		
		
		
		printf("��Ŀ����%s\n",buf.name);
		rec.play_id = play_id;
		printf("�ݳ���ID:");//�ж�
		setbuf(stdin,NULL);
		scanf("%d",&rec.studio_id);
		studio_t buf;
		while( !Studio_Srv_FetchByID(rec.studio_id, &buf)  )
	{
		printf("���ݳ���������!\n");
		printf("�����������ݳ���ID:");
		setbuf(stdin,NULL);
		scanf("%d",&rec.studio_id);
	}
		
		
		printf("��ӳ����(��/��/��):");
		fflush(stdin);
		setbuf(stdin,NULL);
		scanf("%d/%d/%d",&rec.date.year,&rec.date.month,&rec.date.day);

		printf("��ӳʱ��(ʱ/��/��):");
		fflush(stdin);
		setbuf(stdin,NULL);
		scanf("%d/%d/%d",&rec.time.hour,&rec.time.minute,&rec.time.second);

		seat_list_t seat_list;
		List_Init(seat_list,seat_node_t);
		int stand_seatCount = Seat_Srv_FetchValidByRoomID(seat_list,buf.id);
		printf("��λ����(<=%d):",stand_seatCount);//�ж�
		fflush(stdin);
		setbuf(stdin,NULL);
		scanf("%d",&rec.seat_count);
		while( rec.seat_count > stand_seatCount )
	{
		printf("����������λ����(<=%d):",stand_seatCount);
		setbuf(stdin,NULL);
		scanf("%d",&rec.seat_count);
	}
		
		printf("=======================================================\n");

		if (Schedule_Srv_Add(&rec)) {
			newRecCount += 1;
			printf("���ݳ��ƻ����ӳɹ�!\n");

		} else
			printf("���ݳ��ƻ�����ʧ��!\n");

		printf("-------------------------------------------------------\n");
		printf("[A]��������, [R]�����ϲ�:");
		fflush(stdin);

		while (getchar() != '\n');
		setbuf(stdin,NULL);
		scanf("%c", &choice);
	} while ('a' == choice || 'A' == choice);
	system("clear");
	return newRecCount;
}

int Schedule_UI_Modify(int id)
 {
	int rtn = 0;
	schedule_t rec;
	schedule_list_t list;
	int seatcount;

	/*Load record*/
	if (!Schedule_Srv_FetchByID(id, &rec)) {
		printf("���ݳ��ƻ�������!\n�� [Enter] �����ϲ�!\n");
		setbuf(stdin,NULL);
		getchar();
		return 0;
	}
	else
	{
		
	
	

	printf("\n=======================================================\n");
	printf("****************  �޸��ݳ��ƻ�  ****************\n");
	printf("-------------------------------------------------------\n");

		printf("��ĿID:");
		setbuf(stdin,NULL);
		scanf("%d",&rec.play_id);
		play_t buf;
		while( !Play_Srv_FetchByID(rec.play_id,&buf ) )
		{
			printf("�þ�Ŀ������!\n");
			printf("�����������ĿID\n:",rec.play_id);
			setbuf(stdin,NULL);
			scanf("%d",&rec.play_id);
		}
		printf("�ݳ���ID:");//�ж�
		setbuf(stdin,NULL);
		scanf("%d",&rec.studio_id);
		studio_t buf2;
		while( !Studio_Srv_FetchByID(rec.studio_id, &buf2)  )
	{
		printf("���ݳ���������!\n");
		printf("�����������ݳ���ID:");
		setbuf(stdin,NULL);
		scanf("%d",&rec.studio_id);
	}
		
		
		printf("��ӳ����(��/��/��):");
		fflush(stdin);
		setbuf(stdin,NULL);
		scanf("%d/%d/%d",&rec.date.year,&rec.date.month,&rec.date.day);

		printf("��ӳʱ��(ʱ/��/��):");
		fflush(stdin);
		setbuf(stdin,NULL);
		scanf("%d/%d/%d",&rec.time.hour,&rec.time.minute,&rec.time.second);

		seat_list_t seat_list;
		List_Init(seat_list,seat_node_t);
		int stand_seatCount = Seat_Srv_FetchValidByRoomID(seat_list,rec.studio_id);
		printf("��λ����(<=%d):",stand_seatCount);//�ж�
		fflush(stdin);
		setbuf(stdin,NULL);
		scanf("%d",&rec.seat_count);
		while( rec.seat_count > stand_seatCount )
	{
		printf("����������λ����(<=%d):",stand_seatCount);
		setbuf(stdin,NULL);
		scanf("%d",&rec.seat_count);
	}

	

	printf("-------------------------------------------------------\n");

	if (Schedule_Srv_Modify(&rec)) {
		rtn = 1;
		printf(
				"�ɹ��޸ľ�Ŀ��Ϣ!\n���� [Enter] �����ϲ�!\n");
	} else
		printf("�޸ľ�Ŀ��Ϣʧ��!\nPress [Enter]�����ϲ�!\n");

	setbuf(stdin,NULL);
	getchar();
}
	return rtn;
}

int Schedule_UI_Delete(int id) 
{
	int rtn = 0;

	if (Schedule_Srv_DeleteByID(id)) {
		printf(
				"�ɹ�ɾ�����ݳ��ƻ�!\n����[Enter] �����ϲ�!\n");
		rtn = 1;
	} else {
		printf("���ݳ��ƻ�������!\n���� [Enter] �����ϲ�!\n");
	}
	setbuf(stdin,NULL);
	getchar();
	system("clear");
	return rtn;
}
int Schedule_UI_Query(char *play_name) 
{
	play_list_t list_p;
	schedule_list_t list_s;
	List_Init(list_p,play_node_t);
	List_Init(list_s,schedule_node_t);

	Play_Srv_FetchByName(list_p,play_name);
	play_node_t* p;
	List_ForEach(list_p,p)
	{
			Schedule_Srv_FetchByPlay(list_s,p->data.id);
	}
	
	int len = 0,i;
	schedule_list_t s;
	List_ForEach(list_s,s)
	{
		len++;
	}
	//��ӡ�ݳ��ƻ�
	schedule_node_t *pos;
	Pagination_t paging;


	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	paging.totalRecords = len;
	Paging_Locate_FirstPage(list_s, paging);
	
		printf(
				"\n==================================================================\n");
		printf(
				"********************** �ݳ��ƻ���Ϣ **********************\n");
		printf("%8s %8s  %8s  %8s  %8s %8s\n", "�ݳ��ƻ�ID", "��ӳ��ĿID", "�ݳ���ID",
				"��ӳ����", "��ӳʱ��","��λ��");
		printf(
				"------------------------------------------------------------------\n");
		
		Paging_ViewPage_ForEach(list_s, paging, schedule_node_t, pos, i){
			printf("%8d %8d  %8d  %d/%d/%d  %d/%d/%d %8d \n", pos->data.id,
					pos->data.play_id, pos->data.studio_id, pos->data.date.year,
					pos->data.date.month,pos->data.date.day,pos->data.time.hour,
					pos->data.time.minute,pos->data.time.second,pos->data.seat_count);
		}

		printf(
				"------- ��:%2dҳ ----------------------- ҳ�� :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
        printf(
				"******************************************************************\n");
	printf("��[ENTER]�����ϲ�!");
	setbuf(stdin,NULL);
	getchar();
	system("clear");
	return 1;

}

/*???��????????????????????????*/
void Schedule_UI_ListByPlay(play_t *play, schedule_list_t list,
		Pagination_t paging) {
}

void Schedule_UI_MgtEntry(int play_id) {
}
