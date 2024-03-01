#ifndef SATSALES_H_
#define SATSALES_H_

#include"../Service/Sale.h";
#include"../Service/Account.h"


//根据id获得销售额统计
int SatSales_Srv_CompSaleVal(int user_id,ttms_date_t strtime,ttms_date_t endtime);



//
#endif