#include "../Persistence/Sale_Persist.h"
#include "../Persistence/Ticket_Persist.h"
#include "../Common/List.h"

int Sale_Srv_FetchByticket(int ticket_id,sale_t *sale)//����ƱID��ȡ���ۼ�¼ 
{
	return Sale_Perst_SelByTicketID(ticket_id,sale);
}
