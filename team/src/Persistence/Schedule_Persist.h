#ifndef SCHEDPERSIST_H_
#define SCHEDPERSIST_H_

#include "../Service/Schedule.h"



int Schedule_Perst_Insert(schedule_t *data); 

int Schedule_Perst_Update(schedule_t *data);

int Schedule_Perst_RemByID(int ID);

int Schedule_Perst_SelectByID(int ID, schedule_t *buf);

int Schedule_Perst_SelectAll(schedule_list_t list);//���������ݳ��ƻ� 

int Schedule_Perst_SelectByPlay(schedule_list_t buf, int play_id);//���ݾ�ĿID�����ݳ��ƻ� 

int Schedule_Perst_SelectByPlayID(int playID, schedule_t *schedule);
#endif // SCHEDPERSIST_H_
