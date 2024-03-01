#include "SalesAnalysis_UI.h"
#include "../Common/List.h"
//#include "../Service/Account.h"
#include "../Service/Ticket.h"
#include "../Service/Play.h"
#include "../Service/Schedule.h"
#include "../Service/Sale.h"
#include "../Service/SalesAnalysis.h"
#include <stdio.h>
#include <stdlib.h>
const int SALESANALYSIS_PAGE_SIZE = 5;//һҳ������ 
void SalesAnalysis_UI_MgtEntry()//ͳ��Ʊ������ 
{
	int i, id;
	int choice;//ѡ�� 
	salesanalysis_list_t head;
	salesanalysis_node_t *pos;//˫������
	Pagination_t paging;//��ҳ��
	 
	List_Init(head, salesanalysis_node_t);//��ʼ������
	paging.offset = 0;//��¼λ�� 
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;
	
	paging.totalRecords = SalesAnalysis_Srv_StaticSale(head);//��ҳ�� �������� !!!!!!!!!����� 
    SalesAnalysis_Srv_SortBySale(head);//�������򣡣��������� ����� 
	Paging_Locate_FirstPage(head, paging);//��page���ص���ҳ��һ�� 
	do{
		printf("\n===================================================================\n");
		printf(  "************************** Ʊ����Ϣ *******************************\n");
		printf("%6s %20s  %8s  %5s  %20s  %5s %5s %5s\n", 
		       "��Ŀ���", "��Ŀ����", "��Ŀ����","ʱ��", "��ӳʱ��","��������","Ʊ��","Ʊ��");
        printf(
				"-------------------------------------------------------------------\n");
		Paging_ViewPage_ForEach(head, paging, salesanalysis_node_t, pos, i){
		printf("%6d %20s  %8s  %5d  %d/%d/%d->%d/%d/%d  %5d %5d %5d\n"
		,pos->data.play_id
		,pos->data.name
		,pos->data.area
		,pos->data.duration
		,pos->data.start_date.year
		,pos->data.start_date.month
		,pos->data.start_date.day
		,pos->data.end_date.year
		,pos->data.end_date.month
		,pos->data.end_date.day
        ,pos->data.totaltickets
		,pos->data.sales
		,pos->data.price);
		}
	/*int play_id; 	//��Ŀid
	char name[31]; 	//��Ŀ���� 
	char area[9]; 	//��Ŀ���� 
	int duration; 	//��Ŀ����ʱ�� 
	long totaltickets; //��Ŀ�������� 
	long sales; 	//��ĿƱ��(���۶�ͳ��) 
	int price; 		//��ĿƱ�� 
	ttms_date_t start_date; 	//��Ŀ��ӳʱ�� 
	ttms_date_t end_date; 	//��Ŀ��ӳʱ�� 
	*/
	printf(
				"------- ��:%2dҳ ---------------------------------- ҳ�� :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),//��ǰҳ�� 
				Pageing_TotalPages(paging));//��ҳ�� 
	    printf("\n\n"); 
	    printf(
				"*******************************************************************\n");
		printf(
				"[A]��һҳ   |   [B]��һҳ   |   [C]�����ϲ�");
		printf(
				"\n===================================================================\n");
		printf("��������Ҫ���еĲ���:");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);
		switch (choice) {
		case 'a':
		case 'A':
            system("clear");//������� 
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, salesanalysis_node_t);
			}//�Ƿ�Ϊ��һҳ 
			break;
		case 'B':
		case 'b':
            system("clear");//������� 
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, salesanalysis_node_t);
			}//�Ƿ�Ϊ���һҳ 
			break;
		}
	} while (choice != 'C'||choice != 'c');
	List_Destroy(head, salesanalysis_node_t);//�ͷ�����ռ� 
	}

