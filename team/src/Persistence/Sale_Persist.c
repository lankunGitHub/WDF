#include "Sale_Persist.h"
#include "../Common/List.h"
#include "../Service/Sale.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EntityKey_Persist.h"
#include<unistd.h>
#include <assert.h>
#include <string.h>


static const char SALE_DATA_FILE[] = "Sale.dat";
static const char SALE_DATA_TEMP_FILE[] = "SaleTmp.dat";

static const char TICKET_DATA_FILE[]="Ticket.dat";
static const char TICKET_DATA_TEMP_FILE[]="TicketTemp.dat";
static const char TICKET_KEY_NAME[]="Ticket";

int Sale_Perst_SelByTicketID (int ticket_id, sale_t *sale)//����ƱID�������ۼ�¼ 
{
	assert(NULL != sale);

	FILE *fp = fopen(SALE_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	sale_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(sale_t), 1, fp)) {
			if (ticket_id == data.ticket_id) {
				*sale =  data;
				found = 1;
				break;
			};

		}
	}
	fclose(fp);

	return found;

}

int Sale_Perst_SelByID(sale_list_t list, int user_id)
{
    sale_node_t *newNode;
    sale_t data;
    int recCount = 0;

    assert(NULL != list);

    FILE *fp = fopen("Sale.dat", "rb+");
    if (NULL == fp)
    {
        return 0;
    }

    while (!feof(fp))
    {
        if (fread(&data, sizeof(sale_t), 1, fp))
        {
            newNode = (sale_node_t *)malloc(sizeof(sale_node_t));
            if (!newNode)
            {
                printf(
                    "Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
                break;
            }
            if (data.user_id == user_id)
            {
                newNode->data = data;
                List_AddTail(list, newNode);
                recCount++;
            }
        }
    }
    fclose(fp);
    return recCount;
}
