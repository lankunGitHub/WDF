#include <Sale_Persist.h>

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
            if (data.user_id == usrID)
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