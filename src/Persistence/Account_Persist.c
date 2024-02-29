//根据ID载入系统用户
int Accunt_Perst_SelByID(account_list_t list,int user_id)
{
    account_node_t *newNode;
    account_t data;
    int recCount = 0;

    assert(NULL != list);

    FILE *fp = fopen("account.dat", "rb+");
    if (NULL == fp)
    {
        return 0;
    }

    while (!feof(fp))
    {
        if (fread(&data, sizeof(account_t), 1, fp))
        {
            newNode = (account_node_t *)malloc(sizeof(account_node_t));
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