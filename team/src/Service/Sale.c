#include "../Persistence/Sale_Persist.h"
#include "../Persistence/Ticket_Persist.h"
#include "../Common/List.h"

int Sale_Srv_FetchByticket(int ticket_id,sale_t *sale)//根据票ID获取销售记录 
{
	return Sale_Perst_SelByTicketID(ticket_id,sale);
}
