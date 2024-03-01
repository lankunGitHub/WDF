#ifndef TICKET_UI_H_
#define TICKET_UI_H_
#include "../Common/List.h"
#include "../Service/Ticket.h"
#include "../Service/Seat.h"
#include "../Service/Schedule.h"

static const int TICKET_PAGE_SIZE=8;

int Ticket_UI_MgtEntry(int schedule_id);//生成演出票界面 

void Ticket_UI_Query(void);//查询演出票界面 

int Ticket_UI_ShowTicket (ticket_list_t list);//显示演出票界面 





#endif /* TICKET_UI_H_ */
