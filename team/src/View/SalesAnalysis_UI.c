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
const int SALESANALYSIS_PAGE_SIZE = 5;//一页的数量 
void SalesAnalysis_UI_MgtEntry()//统计票房界面 
{
	int i, id;
	int choice;//选择 
	salesanalysis_list_t head;
	salesanalysis_node_t *pos;//双向链表
	Pagination_t paging;//分页器
	 
	List_Init(head, salesanalysis_node_t);//初始化链表
	paging.offset = 0;//记录位置 
	paging.pageSize = SALESANALYSIS_PAGE_SIZE;
	
	paging.totalRecords = SalesAnalysis_Srv_StaticSale(head);//总页数 载入数据 !!!!!!!!!已完成 
    SalesAnalysis_Srv_SortBySale(head);//数据排序！！！！！！ 已完成 
	Paging_Locate_FirstPage(head, paging);//将page返回到首页第一个 
	do{
		printf("\n===================================================================\n");
		printf(  "************************** 票房信息 *******************************\n");
		printf("%6s %20s  %8s  %5s  %20s  %5s %5s %5s\n", 
		       "剧目编号", "剧目名字", "剧目区域","时长", "上映时间","上座数量","票房","票价");
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
	/*int play_id; 	//剧目id
	char name[31]; 	//剧目名称 
	char area[9]; 	//剧目区域 
	int duration; 	//剧目播放时长 
	long totaltickets; //剧目上座数量 
	long sales; 	//剧目票房(销售额统计) 
	int price; 		//剧目票价 
	ttms_date_t start_date; 	//剧目上映时间 
	ttms_date_t end_date; 	//剧目下映时间 
	*/
	printf(
				"------- 共:%2d页 ---------------------------------- 页数 :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),//当前页号 
				Pageing_TotalPages(paging));//总页号 
	    printf("\n\n"); 
	    printf(
				"*******************************************************************\n");
		printf(
				"[A]上一页   |   [B]下一页   |   [C]返回上层");
		printf(
				"\n===================================================================\n");
		printf("请输入您要进行的操作:");
		fflush(stdin);
		scanf("%c", &choice);
		fflush(stdin);
		switch (choice) {
		case 'a':
		case 'A':
            system("clear");//清理界面 
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, salesanalysis_node_t);
			}//是否为第一页 
			break;
		case 'B':
		case 'b':
            system("clear");//清理界面 
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, salesanalysis_node_t);
			}//是否为最后一页 
			break;
		}
	} while (choice != 'C'||choice != 'c');
	List_Destroy(head, salesanalysis_node_t);//释放链表空间 
	}

