#ifndef SCHEDULE_UI_H_
#define SCHEDULE_UI_H_
#include "../Common/List.h"
#include "../Service/Schedule.h"
#include "../Service/Play.h"

static const int SCHEDULE_PAGE_SIZE=5;

int Schedule_UI_MgtEnt();//生成演出界面 

int Schedule_UI_Add(int play_id);//添加新演出计划页面 

int Schedule_UI_Modify(int id);//修改演出计划界面 

int Schedule_UI_Delete(int id);//删除演出计划界面 

int Schedule_UI_Query(char *play_name);//根据剧目名称获取演出计划 

void Schedule_UI_MgtEntry(int play_id);//安排演出界面 


void Schedule_UI_ListByPlay(play_t *play, schedule_list_t list, Pagination_t paging);

void Schedule_UI_ListAll(void);//查询演出界面 

#endif // SCHEDULES_UI_H_

