#ifndef CLERK_PAGE_SIZE
#define CLERK_PAGE_SIZE 5

#include "../View/StaSales_UI.h"
#include "../Service/SatSales.h"
#include <time.h>
extern account_t Login;
void StaSales_UI_MgtEntry(void)
{
    printf("\n=======================================================\n");
    printf("****************  Update Projection SaleRoom  ****************\n");
    printf("-------------------------------------------------------\n\n\n");

    if (account_t.account_type_t == 1)
        SatSales_UI_Clerk(login);
    else if (account_t.account_type_t == 2)
        SatSales_UI_Self(account_t login);
}

// 统计售票员销售额界面
void SatSales_UI_Clerk(account_t login)
{
    int id, amount = 0, i;
    char choose;
    account_list_t clerk;
    account_node_t *pos;
    Pagination_t paging;

    List_Init(head, account_node_t);
    paging.offset = 0;
    paging.pageSize = CLERK_PAGE_SIZE;

    paging.totalRecords = Account_Srv_FetchAll(head);
    Paging_Locate_FirstPage(head, paging);
    do
    {
        printf(
            "\n==================================================================\n");
        printf(
            "********************** Projection Clerk List **********************\n");
        printf("%5s  %18s  %10s\n", "ID", "Name", "Type");
        printf(
            "------------------------------------------------------------------\n");
        Paging_ViewPage_ForEach(head, paging, account_node_t, pos, i)
        {
            printf("%5d  %18s  %5d\n", pos->date.id,
                   pos->data.username, pos->account_tyoe_t);
        }

        printf(
            "------- Total Records:%2d ----------------------- Page %2d/%2d ----\n",
            paging.totalRecords, Pageing_CurPage(paging),
            Pageing_TotalPages(paging));
        printf(
            "******************************************************************\n");
        printf(
            "[P]revPage|[N]extPage | [C]heck");
        printf(
            "\n==================================================================\n");
        printf("Your Choice:");
        fflush(stdin);
        scanf("%c", &choose);
        fflush(stdin);
        switch (choose)
        {
        case 'p':
        case 'P':
            if (!Pageing_IsFirstPage(paging))
            {
                Paging_Locate_OffsetPage(head, paging, -1, studio_node_t);
            }
            break;
        case 'n':
        case 'N':
            if (!Pageing_IsLastPage(paging))
            {
                Paging_Locate_OffsetPage(head, paging, 1, studio_node_t);
            }
            break;
        case "C":
        case "c":
        system("clear");
            printf("Please enter the ID:");
            scanf("%d", &id);
            ttms_date_t curdate;
            ttms_date_t startdate;
            ttms_date_t enddate;
            time_t rawtime;
            struct tm *timeinfo;

            time(&rawtime);
            timeinfo = localtime(&rawtime);
            curdate.year = timeinfo->tm_year + 1900;
            curdate.month = timeinfo->tm_mon;
            curdate.day = timeinfo->tm_mday;
            printf("=======================================\n");
            printf("[1]Dayly sales | [2]Monthly sales | [0]return\n");
            printf("---------------------------------------\n");
            printf("Now,you can enter your choice: ");
            do
            {
                int choice;
                scanf("%d", &choice);
                switch (choice)
                {
                case 1:
                    amount = SatSales_Srv_CompSaleVal(id, curdate, curdate);
                    printf("Your") break;
                case 2:
                    printf("Please enter the start date(such as 2024-2-29):") while (1)
                    {
                        if (3 > scanf("%d-%d-%d", &startdate.year, &startdate.month, &startdate.day))
                        {
                            printf("You enter wrong date!!!try again");
                            continue;
                        }
                        if (startdate.year < curdate.year)
                        {
                            if (startdate.month <= 12)
                            {
                                if (startdate.month % 2 == 1)
                                {
                                    if (startdate.day <= 31)
                                        break;
                                }
                                else
                                {
                                    if (startdate.day <= 30)
                                        break;
                                }
                            }
                        }
                        if (startdate.year = curdate.year)
                        {
                            if (startdate.month <= curdate.month)
                            {
                                if (startdate.month % 2 == 1)
                                {
                                    if (startdate.day <= 31)
                                        break;
                                }
                                else
                                {
                                    if (startdate.day <= 30)
                                        break;
                                }
                            }
                        }
                        printf("You enter wrong date!!!try again");
                    }
                    printf("Now,Please enter the end date(such as 2024-2-29):") while (1)
                    {
                        if (3 > scanf("%d-%d-%d", &enddate.year, &enddate.month, &enddate.day))
                        {
                            printf("You enter wrong date!!!try again");
                            continue;
                        }
                        if (eneddate.year < curdate.year)
                        {
                            if (enddate.month <= 12)
                            {
                                if (enddate.month % 2 == 1)
                                {
                                    if (enddate.day <= 31)
                                        break;
                                }
                                else
                                {
                                    if (enddate.day <= 30)
                                        break;
                                }
                            }
                        }
                        if (enddate.year = curdate.year)
                        {
                            if (enddate.month <= curdate.month)
                            {
                                if (enddate.month % 2 == 1)
                                {
                                    if (enddate.day <= 31)
                                        break;
                                }
                                else
                                {
                                    if (enddate.day <= 30)
                                        break;
                                }
                            }
                        }
                        printf("You enter wrong date!!!try again");
                    }
                    amount = SatSales_Srv_CompSaleVal(id, curdate, curdate);
                    break;
                case 0:
                    break;
                default:
                    printf("You enter wrong choice!!!Please try again") break;
                }
            } while (choice != 0);
        }
    } while (choice != 'r' && choice != 'R');
}

// 统计个人销售额界面
void SatSales_UI_Self(account_t login)
{
    int id = login.id, amount = 0;
    ttms_date_t curdate;
    ttms_date_t startdate;
    ttms_date_t enddate;
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    curdate.year = timeinfo->tm_year + 1900;
    curdate.month = timeinfo->tm_mon;
    curdate.day = timeinfo->tm_mday;
    printf("=======================================\n");
    printf("[1]Dayly sales | [2]Monthly sales | [0]return\n");
    printf("---------------------------------------\n");
    printf("Now,you can enter your choice: ");
    do
    {
        int choice;
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            amount = SatSales_Srv_CompSaleVal(id, curdate, curdate);
            printf("Your") break;
        case 2:
            printf("Please enter the start date(such as 2024-2-29):") while (1)
            {
                if (3 > scanf("%d-%d-%d", &startdate.year, &startdate.month, &startdate.day))
                {
                    printf("You enter wrong date!!!try again");
                    continue;
                }
                if (startdate.year < curdate.year)
                {
                    if (startdate.month <= 12)
                    {
                        if (startdate.month % 2 == 1)
                        {
                            if (startdate.day <= 31)
                                break;
                        }
                        else
                        {
                            if (startdate.day <= 30)
                                break;
                        }
                    }
                }
                if (startdate.year = curdate.year)
                {
                    if (startdate.month <= curdate.month)
                    {
                        if (startdate.month % 2 == 1)
                        {
                            if (startdate.day <= 31)
                                break;
                        }
                        else
                        {
                            if (startdate.day <= 30)
                                break;
                        }
                    }
                }
                printf("You enter wrong date!!!try again");
            }
            printf("Now,Please enter the end date(such as 2024-2-29):") while (1)
            {
                if (3 > scanf("%d-%d-%d", &enddate.year, &enddate.month, &enddate.day))
                {
                    printf("You enter wrong date!!!try again");
                    continue;
                }
                if (eneddate.year < curdate.year)
                {
                    if (enddate.month <= 12)
                    {
                        if (enddate.month % 2 == 1)
                        {
                            if (enddate.day <= 31)
                                break;
                        }
                        else
                        {
                            if (enddate.day <= 30)
                                break;
                        }
                    }
                }
                if (enddate.year = curdate.year)
                {
                    if (enddate.month <= curdate.month)
                    {
                        if (enddate.month % 2 == 1)
                        {
                            if (enddate.day <= 31)
                                break;
                        }
                        else
                        {
                            if (enddate.day <= 30)
                                break;
                        }
                    }
                }
                printf("You enter wrong date!!!try again");
            }
            amount = SatSales_Srv_CompSaleVal(id, curdate, curdate);
            break;
        case 0:
            break;
        default:
            printf("You enter wrong choice!!!Please try again") break;
        }
    } while (choice != 0);
}