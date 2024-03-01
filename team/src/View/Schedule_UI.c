#include "Schedule_UI.h"
#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"
#include "../Service/Studio.h"
#include "../Service/Seat.h"
#include <stdio.h>
#include <stdlib.h>
#include "./Ticket_UI.h"

void Schedule_UI_ListAll(void) //查询演出界面 
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
        
		printf(
				"\n==========================================================\n");
		printf(
				"********************** 演出计划信息 **********************\n");
		printf("%8s %8s  %8s  %8s  %8s %8s\n", "演出计划ID", "上映剧目ID", "演出厅ID",
				"放映日期", "放映时间","座位数");
		printf(
				"----------------------------------------------------------\n");
		
		Paging_ViewPage_ForEach(head, paging, schedule_node_t, pos, i){
			printf("%8d %8d  %8d  %d/%d/%d  %d/%d/%d %8d \n", pos->data.id,
					pos->data.play_id, pos->data.studio_id, pos->data.date.year,
					pos->data.date.month,pos->data.date.day,pos->data.time.hour,
					pos->data.time.minute,pos->data.time.second,pos->data.seat_count);
		}
	printf(
				"------- 共:%2d页 ------------------------- 页数 :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        
        
        printf("\n\n\n\n"); 
        
        
        printf(
				"**********************************************************\n");
		printf(
				"[1]上一页    |   [2]下一页   |   [3] 根据名字筛选演出计划\n[0]返回上层  |");
		printf(
				"\n\n\n\n==========================================================\n");
        printf("请输入您要进行的操作:");
		fflush(stdin);
        setbuf(stdin,NULL);
		scanf("%d", &choice);
		setbuf(stdin,NULL);
		fflush(stdin);


     
		switch (choice) {
		case 3:
			
            system("clear");
			printf("请输入要查询的剧目名字:");
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

    
}
int Schedule_UI_Query(char *play_name) //根据剧目名称获取演出计划 
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
	//打印演出计划
	schedule_node_t *pos;
	Pagination_t paging;


	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;

	paging.totalRecords = len;
	Paging_Locate_FirstPage(list_s, paging);
	
		printf(
				"\n==================================================================\n");
		printf(
				"********************** 演出计划信息 **********************\n");
		printf("%8s %8s  %8s  %8s  %8s %8s\n", "演出计划ID", "上映剧目ID", "演出厅ID",
				"放映日期", "放映时间","座位数");
		printf(
				"------------------------------------------------------------------\n");
		
		Paging_ViewPage_ForEach(list_s, paging, schedule_node_t, pos, i){
			printf("%8d %8d  %8d  %d/%d/%d  %d/%d/%d %8d \n", pos->data.id,
					pos->data.play_id, pos->data.studio_id, pos->data.date.year,
					pos->data.date.month,pos->data.date.day,pos->data.time.hour,
					pos->data.time.minute,pos->data.time.second,pos->data.seat_count);
		}

		printf(
				"------- 共:%2d页 ----------------------- 页数 :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
        printf(
				"******************************************************************\n");
	printf("按[ENTER]返回上层!");
	setbuf(stdin,NULL);
	getchar();
	system("clear");
	return 1;

}

//
void Schedule_UI_ListByPlay(play_t *play, schedule_list_t list,
		Pagination_t paging) {
			
			
}

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
				"************************** 演出计划信息 ************************\n");
		printf("%8s %8s  %8s  %8s    %8s      %8s\n", "演出计划ID", "上映剧目ID", "演出厅ID",
				"放映日期", "放映时间","座位数");
		printf(
				"------------------------------------------------------------------\n");
		
		Paging_ViewPage_ForEach(head, paging, schedule_node_t, pos, i){
			printf("%6d   %8d  %8d      %d/%d/%d    %d:%d:%d %8d \n", pos->data.id,
					pos->data.play_id, pos->data.studio_id, pos->data.date.year,
					pos->data.date.month,pos->data.date.day,pos->data.time.hour,
					pos->data.time.minute,pos->data.time.second,pos->data.seat_count);
		}

		printf(
				"--------------- 共:%2d页 ----------------------- 页数 :%2d/%2d -----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        
        
        printf("\n\n\n\n"); 
        
        
        printf(
				"******************************************************************\n");
		printf(
				"[1]上一页         |   [2]下一页         |   [3]添加演出计划   |\n[4]删除演出计划   |   [5]修改演出计划   |   [6]生成演出票     |\n[0]返回上层       |");
		printf(
				"\n\n\n\n==================================================================\n");
        printf("请输入您要进行的操作:");
		fflush(stdin);
        setbuf(stdin,NULL);
		scanf("%d", &choice);
		setbuf(stdin,NULL);
		fflush(stdin);


     
		switch (choice) {
		case 3:
            system("clear");
			printf("请输入要生成的演出计划的剧目ID:");
			scanf("%d", &id);
			if (Schedule_UI_Add(id)) 
			{
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				Paging_Locate_LastPage(head, paging, schedule_node_t);
			}
			break;
		case 4:
            system("clear");
			printf("请输入要删除的演出计划ID:");
			scanf("%d", &id);
			if (Schedule_UI_Delete(id)) {	
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				List_Paging(head, paging, schedule_node_t);
			}
			break;
		case 5:
            system("clear");
			printf("请输入要修改的演出计划ID");
			scanf("%d", &id);
			if (Schedule_UI_Modify(id)) {	
				paging.totalRecords = Schedule_Srv_FetchAll(head);
				List_Paging(head, paging, schedule_node_t);
			}
			break;
		case 6:
            system("clear");
			int id;
			printf("请选择要管理哪个演出计划的演出票(ID):");
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

    system("clear");
	List_Destroy(head, schedule_node_t);

    return 0;
}




//安排演出界面 
void Schedule_UI_MgtEntry(int play_id) {

}

