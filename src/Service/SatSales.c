#include"../Service/SatSales.h"



int SatSales_Srv_CompSaleVal(int user_id,ttms_date_t strdate,ttms_date_t enddate)
{
    int amount=0;
	sale_list_t saleList;
	sale_list_t p;
	List_Init(saleList,sale_node_t);
	Sale_Perst_SelByID(saleList,user_id);//saleList存储id对应的销售记录链表
	List_ForEach(saleList,p)
	{
		if( (p->data.date.year)*10000+(p->data.date.month)*100+(p->data.date.day)  >=  (strdate.year)*10000+(strdate.month)*100+(strdate.day)  &&  (p->data.date.year)*10000+(p->data.date.month)*100+(p->data.date.day)  <=  (enddate.year)*10000+(enddate.month)*100+(enddate.day) )
		{
			amount+=value;
		}
	}
}
