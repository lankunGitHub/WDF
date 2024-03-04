#ifndef SALETICKET_UI_H_
#define SALETICKET_UI_H_


//接口其他文件 
#include"../Service/Play.h"
#include"../Srevice/Seat.h"
#include"../Srevice/Account.h"
#include"../Srevice/TIcket.h"
#include"../Srevice/Schedule.h"
//退票界面
//查找所购买的票 
void Sale_UI_ShowScheduler(int playID);
// 
void Sale_UI_ShowScheduler1(int playID);
//查找票是否被预定 
int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList);

//所需购买的电影票的信息 
void Sale_UI_MgtEntry(void);

//退票界面
//标识符   TTMS_SCU_Sale_UI_RetfundTicket
void Sale_UI_RetfundTicket();
//所购买票的信息 
void Sale_UI_ShowTicket(int schedule_id);

void Sale_UI_ShowTicket1(int schedule_id);
//具体退票的内容 
int Sale_UI_SellTicket1(ticket_list_t tickList,seat_list_t seatList);

void Sale_UI_ShowTicketBypic(int schedule_id);
#endif