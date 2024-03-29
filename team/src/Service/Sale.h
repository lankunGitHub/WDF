#ifndef SALE_H_
#define SALE_H_
#include "../Common/common.h"
//#include "Account.h"
#include "Ticket.h"
#include "Schedule.h"

//??????????????????
typedef enum{
	SALE_SELL=1,	//???
	SALE_RETURN=-1	//???
}sale_type_t;


typedef struct {
	long id;      		//??????ID
	int user_id;		//????ID
	int ticket_id;		//?ID
	ttms_date_t date ;	//????????
	ttms_time_t time;	//???????
	int value;			//???
	sale_type_t type; //????????
}sale_t;

//???????
typedef struct sale_node {
	sale_t data;
	struct sale_node *next, *prev;
} sale_node_t, *sale_list_t;

//????????????
int Sale_Srv_Add(sale_t *data);
//??????
int Ticket_Srv_Modify (const ticket_t *data);


//int Ticket_Srv_FetchBySchID(ticket_list_t list, int schedule_id);


int Ticket_Srv_FetchBySchID(ticket_list_t list, int schedule_id);


//int Ticket_Srv_FetchBySchID(int ID, ticket_list_t list);

ticket_node_t * Ticket_Srv_FetchBySeatID (ticket_list_t list, int seat_id);

int Sale_Srv_FetchAll(sale_list_t list);

int Sale_Srv_FetchByticket(int ticket_id,sale_t *sale);

int Ticket_Srv_FetchBySchID2(ticket_list_t  list,int schedule_id);
#endif //SALE_H_

