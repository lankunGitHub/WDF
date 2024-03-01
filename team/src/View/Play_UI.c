#include "Play_UI.h"
#include "Schedule_UI.h"

#include "../Common/List.h"
#include "../Service/Play.h"
#include "Schedule_UI.h"

#include <stdio.h>
#include <stdlib.h>

void Play_UI_MgtEntry() //��þ�Ŀ��Ϣ 
{
	 play_list_t head;
	play_node_t *pos;
	Pagination_t paging;
	int i, id;
	int choice;

	
	List_Init(head, play_node_t);
	paging.offset = 0;
	paging.pageSize = PLAY_PAGE_SIZE;

	
	
	paging.totalRecords = Play_Srv_FetchAll(head);
	Paging_Locate_FirstPage(head, paging);
   
    /* int cnt = 0; */
	do {
     
		printf(
				"\n==================================================================\n");
		printf(
				"************************* ��Ŀ��Ϣ *******************************\n");
		printf("%2s   %20s   %10s   %5s  %18s       %5s\n", "ID", "��Ŀ����", "��Ʒ����",
				"ʱ��", "��ʼ->����","Ʊ��");
		printf(
				"------------------------------------------------------------------\n");
		    //???????
		Paging_ViewPage_ForEach(head, paging, play_node_t, pos, i)
        {
			printf("%2d %20s  %10s  %5d  %4d/%02d/%02d->%4d/%02d/%02d  %5d\n", pos->data.id,pos->data.name,pos->data.area,pos->data.duration
            ,pos->data.start_date.year,pos->data.start_date.month,pos->data.start_date.day,pos->data.end_date.year,pos->data.end_date.month,pos->data.end_date.day,pos->data.price);
		}
		printf(
				"--------------- ��:%2d�� ----------------------- ҳ�� :%2d/%2d ------\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        
        
        printf("\n\n\n\n"); 
        
       
        printf(
				"******************************************************************\n");
		printf(
				"[1]��һҳ     |   [2]��һҳ      |   [3]����¾�Ŀ |   [4]ɾ����Ŀ\n[5]�޸ľ�Ŀ   |   [6]��ѯ��Ŀ    |   [7]�����ݳ�   |   [0]�����ϲ�");
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
			if (Play_UI_Add()) 
			{
				paging.totalRecords = Play_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, play_node_t);
			}
			break;
		case 4:
            system("clear");
			printf("������Ҫɾ���ľ�ĿID:");



			scanf("%d", &id);
			if (Play_UI_Delete(id)) {	
				paging.totalRecords = Play_Srv_FetchAll(head);
				List_Paging(head, paging, play_node_t);
			}
			break;
		case 5:
            system("clear");
			printf("������Ҫ�޸ĵľ�ĿID");
			scanf("%d", &id);
			if (Play_UI_Modify(id)) {	
				paging.totalRecords = Play_Srv_FetchAll(head);
				List_Paging(head, paging, play_node_t);
			}
			break;
		case 6:
            system("clear");
			printf("������Ҫ��ѯ�ľ�ĿID:");
			scanf("%d", &id);
			Play_UI_Query(id);
			paging.totalRecords = Play_Srv_FetchAll(head);
			List_Paging(head, paging, play_node_t);
			break;
		case 7:
			system("clear");
			Schedule_UI_MgtEnt();
			paging.totalRecords = Play_Srv_FetchAll(head);
			List_Paging(head, paging, play_node_t);
			break;
		case 1:
            system("clear");
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
			}
			break;
		case 2:
            system("clear");
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
			}
			break;
		}


	} while (choice != 0);
	
	 List_Destroy(head, play_node_t);
}






int Play_UI_Add(void)//����¾�Ŀ���� 
 {
	 play_t rec;
	int newRecCount = 0;
	int  choice;

	do {
		system("clear");
		printf("\n=======================================================\n");
		printf("****************      ����¾�Ŀ      ****************\n");
		printf("-------------------------------------------------------\n");
		//??????????
		printf("�¾�Ŀ����:");
		fflush(stdin);
		setbuf(stdin,NULL);
		gets(rec.name);

		printf("\n��Ŀ���� [1].Ӱ�� | [2].Ϸ�� | [3].���ֻ�:");
		setbuf(stdin,NULL);
		scanf("%d", &rec.type);
		while(!(rec.type == 1 || rec.type == 2  || rec.type == 3))
		{
				printf("���벻�Ϸ�!����������:\n");
				setbuf(stdin,NULL);
				scanf("%d", &rec.type);
		}
		
		
		
		printf("\n��Ʒ����:");
		setbuf(stdin,NULL);
		scanf("%s", &(rec.area));

		printf("\n�ʺ�����: [1].��ͯ | [2].������ | [3].����:");
		setbuf(stdin,NULL);
		scanf("%d", &(rec.rating));
		while(!(rec.rating == 1 || rec.rating == 2  || rec.rating == 3))
		{
				printf("���벻�Ϸ�!����������:");
				setbuf(stdin,NULL);
				scanf("%d", &rec.rating);
		}

		printf("\nʱ��(����):");
		setbuf(stdin,NULL);
		scanf("%d", &(rec.duration));

		printf("\n��ӳʱ�� (��/��/��):");
		setbuf(stdin,NULL);
		scanf("%d/%d/%d", &(rec.start_date.year),&(rec.start_date.month),&(rec.start_date.day));

		printf("\n�¼�ʱ�� (��/��/��):");
		setbuf(stdin,NULL);
		scanf("%d/%d/%d", &(rec.end_date.year),&(rec.end_date.month),&(rec.end_date.day));
		while(!(rec.start_date.year <= rec.end_date.year ))
		{
				printf("���벻�Ϸ�!����������(�¼����ڱ���������ӳ����):");
				setbuf(stdin,NULL);
				scanf("%d/%d/%d", &(rec.end_date.year),&(rec.end_date.month),&(rec.end_date.day));
		}

		printf("\nƱ�� (Ԫ) :");
		setbuf(stdin,NULL);
		scanf("%d", &(rec.price));
		
		printf("=======================================================\n");

		
		if (Play_Srv_Add(&rec))
		 {
			newRecCount += 1;
			printf("�ɹ�����¾�Ŀ!\n");
		} else
			printf("�¾�Ŀ���ʧ��!\n");

		printf("-------------------------------------------------------\n");
		printf("[1]�������, [0]�����ϲ�");
		
		setbuf(stdin,NULL);
		scanf("%d", &choice);
		
	} while (choice != 0);


	system("clear");
	return newRecCount;
}

int Play_UI_Modify(int id)//�޸ľ�Ŀ���� 
 {
	play_t rec;
	int rtn = 0;
	int newrow, newcolumn;
	play_list_t list;
	int seatcount;

	/*Load record*/
	if (!Play_Srv_FetchByID(id, &rec)) {
		printf("�þ�Ŀ������!\n�� [Enter] �����ϲ�!\n");
		setbuf(stdin,NULL);
		getchar();
		return 0;
	}
	else
	{
		printf("�þ�Ŀ����!\n");
	}
	

	printf("\n=======================================================\n");
	printf("****************  �޸ľ�Ŀ��Ϣ  ****************\n");
	printf("-------------------------------------------------------\n");

	printf("��Ŀ����:");
		fflush(stdin);
		setbuf(stdin,NULL);
		gets(rec.name);

		printf("\n��Ŀ���� [1].Ӱ�� | [2].Ϸ�� | [3].���ֻ�:");
		setbuf(stdin,NULL);
		scanf("%d", &rec.type);
		while(!(rec.type == 1 || rec.type == 2  || rec.type == 3))
		{
				printf("���벻�Ϸ�!����������:\n");
				setbuf(stdin,NULL);
				scanf("%d", &rec.type);
		}
		
		
		
		printf("\n��Ʒ����:");
		setbuf(stdin,NULL);
		scanf("%s", &(rec.area));

		printf("\n�ʺ�����: [1].��ͯ | [2].������ | [3].����");
		setbuf(stdin,NULL);
		scanf("%d", &(rec.rating));
		while(!(rec.rating == 1 || rec.rating == 2  || rec.rating == 3))
		{
				printf("���벻�Ϸ�!����������:");
				setbuf(stdin,NULL);
				scanf("%d", &rec.rating);
		}

		printf("\nʱ��(����):");
		setbuf(stdin,NULL);
		scanf("%d", &(rec.duration));

		printf("\n��ӳʱ�� (��/��/��):");
		setbuf(stdin,NULL);
		scanf("%d/%d/%d", &(rec.start_date.year),&(rec.start_date.month),&(rec.start_date.day));

		printf("\n�¼�ʱ�� (��/��/��):");
		setbuf(stdin,NULL);
		scanf("%d/%d/%d", &(rec.end_date.year),&(rec.end_date.month),&(rec.end_date.day));
		while(!(rec.start_date.year <= rec.end_date.year ))
		{
				printf("���벻�Ϸ�!����������(�¼����ڱ���������ӳ����):");
				setbuf(stdin,NULL);
				scanf("%d/%d/%d", &(rec.end_date.year),&(rec.end_date.month),&(rec.end_date.day));
		}

		printf("\nƱ�� (Ԫ) :");
		setbuf(stdin,NULL);
		scanf("%d", &(rec.price));

	

	printf("-------------------------------------------------------\n");

	if (Play_Srv_Modify(&rec)) {
		rtn = 1;
		printf(
				"�ɹ��޸ľ�Ŀ��Ϣ!\n���� [Enter] �����ϲ�!\n");
	} else
		printf("�޸ľ�Ŀ��Ϣʧ��!\nPress [Enter]�����ϲ�!\n");

	setbuf(stdin,NULL);
	getchar();
	 system("clear");
	return rtn;
}

int Play_UI_Delete(int id) //ɾ����Ŀ���� 
{
	int rtn = 0;

	if (Play_Srv_DeleteByID(id)) {
		printf(
				"�ɹ�ɾ���þ�Ŀ!\n����[Enter] �����ϲ�!\n");
		rtn = 1;
	} else {
		printf("�þ�Ŀ������!\n���� [Enter] �����ϲ�!\n");
	}
	setbuf(stdin,NULL);
	getchar();
	 system("clear");
	return rtn;
}

int Play_UI_Query(int id)//��ѯ��Ŀ���� 
 {
	play_t rec;
	if (!Play_Srv_FetchByID(id, &rec)) {
		printf("�þ�Ŀ������!\n�� [Enter] �����ϲ�!\n");
		setbuf(stdin,NULL);
		getchar();
		system("clear");
		return 0;
	}
	else
	{
		printf(
				"\n==================================================================\n");
		printf(
				"********************** ��Ŀ��Ϣ **********************\n");
		printf("%5s %30s  %9s  %5s  %22s  %5s\n", "ID", "��Ŀ����", "��Ʒ����",
				"ʱ��", "��ʼ->����","Ʊ��");
		printf(
				"------------------------------------------------------------------\n");

				printf("%5d %15s  %9s  %5d  %d/%d/%d->%d/%d/%d  %5d\n", rec.id,rec.name,rec.area,rec.duration
            ,rec.start_date.year,rec.start_date.month,rec.start_date.day,rec.end_date.year,rec.end_date.month,rec.end_date.day,rec.price);
		
		
		printf("\n�� [Enter] �����ϲ�!\n");
		setbuf(stdin,NULL);
		getchar();
		system("clear");
	
	}
	return 0;
}
