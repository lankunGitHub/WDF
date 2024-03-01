#ifndef SCHEDPERSIST_H_
#define SCHEDPERSIST_H_

#include "../Service/Schedule.h"



int Schedule_Perst_Insert(schedule_t *data); 

int Schedule_Perst_Update(schedule_t *data);

int Schedule_Perst_RemByID(int ID);

int Schedule_Perst_SelectByID(int ID, schedule_t *buf);

int Schedule_Perst_SelectAll(schedule_list_t list);//载入所有演出计划 

int Schedule_Perst_SelectByPlay(schedule_list_t buf, int play_id);//根据剧目ID载入演出计划 

#endif // SCHEDPERSIST_H_
