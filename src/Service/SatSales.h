#define NAME_MAX 257

#ifndef SATSALES_H_
#define SATSALES_H_

#include"../Service/Sale.h";
#include"../Service/Account.h"


/*typedef enum
{
    SALE_SELL=1,  //买票
    SALE_REFOUND=-1   //卖票
}sale_type_t;

typedef struct 
{
    long id;  //销售记录ID
    int user_id;  //销售员ID
    int ticket_id;  //票ID
    ttms_date_t date;   //处理日期
    ttms_time_t time;   //处理时间
    int value;   //票价
    sale_type_t type;   //交易类型
}sale_t;

typedef struct sale_node
{
    sale_t date;
    struct sale_node* next;
    struct sale_node* prev;
}sale_node_t,*sale_node_t;
*/
//根据id获得销售额统计
int SatSales_Srv_CompSaleVal(int user_id,ttms_date_t strtime,ttms_date_t endtime);



//
#endif