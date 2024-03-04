#include "../Service/Seat.h"
#include "../Service/Studio.h"
#include "../Service/Sale.h"
#include "../Common/List.h"
#include "./Seat_UI.h"

static const char SALE_KEY_NAME[] = "Sale";

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define SIZE 5

void Sale_UI_ShowScheduler(int playID)
{
    play_t buf;
    int i;
    int choice;
    i = Play_Srv_FetchByID(playID, &buf);
    if (i == 0)
    {
        printf("�˾�Ŀid�����ڣ�");
        return;
    }

    schedule_list_t flag;
    List_Init(flag, schedule_node_t);
    Schedule_Srv_FetchByPlay(flag, playID); // flagΪ��Ŀid����Ӧ�������ݳ��ƻ�����

    schedule_list_t pos;

    Pagination_t paging;
    int len = 0;
    List_ForEach(flag, pos)
    {
        len++;
    }
    paging.offset = 0;
    paging.pageSize = SCHEDULE_PAGE_SIZE;
    paging.totalRecords = len;
    Paging_Locate_FirstPage(flag, paging);

    do
    {

        printf(
            "\n==================================================================\n");
        printf(
            "************************** �ݳ��ƻ���Ϣ **************************\n");
        printf("%8s %8s %8s %8s %8s %8s\n", "�ݳ��ƻ�ID", "��ӳ��ĿID", "�ݳ���ID",
               "��ӳ����", "��ӳʱ��", "��λ��");
        printf(
            "------------------------------------------------------------------\n");

        Paging_ViewPage_ForEach(flag, paging, schedule_node_t, pos, i)
        {
            printf("%8d %8d %8d %d/%d/%d %d/%d/%d %8d \n", pos->data.id,
                   pos->data.play_id, pos->data.studio_id, pos->data.date.year,
                   pos->data.date.month, pos->data.date.day, pos->data.time.hour,
                   pos->data.time.minute, pos->data.time.second, pos->data.seat_count);
        }

        printf(
            "------- ��:%2dҳ -------------------------------- ҳ�� :%2d/%2d ----\n",
            paging.totalRecords, Pageing_CurPage(paging),
            Pageing_TotalPages(paging));

        printf("\n\n\n\n");
        printf(
            "******************************************************************\n");

        printf("==================================================================\n");
        printf("[1]��һҳ [2]��һҳ [3]�б���ʾ�ݳ�Ʊ \n[4]ͼ����ʾ�ݳ�Ʊ [0]����\n");
        printf("==================================================================\n");

        fflush(stdin);
        printf("�����룺");
        fflush(stdin);
        scanf("%d", &choice);
        fflush(stdin);
        system("clear");

        int x;
        switch (choice)
        {
        case 3:
            system("clear");
            printf("�������ݳ��ƻ�id��");
            scanf("%d", &x);
            Sale_UI_ShowTicket(x); // �����ݳ��ƻ�id����ȡƱ
            break;
        case 4:
            system("clear");
            printf("�������ݳ��ƻ�id��");
            scanf("%d", &x);
            Sale_UI_ShowTicketBypic(x); // �����ݳ��ƻ�id����ȡƱ
            break;
        case 1:
            system("clear");
            if (!Pageing_IsFirstPage(paging))
            {
                Paging_Locate_OffsetPage(flag, paging, -1, schedule_node_t);
            }
            break;
        case 2:
            system("clear");
            if (!Pageing_IsLastPage(paging))
            {
                Paging_Locate_OffsetPage(flag, paging, 1, schedule_node_t);
            }
            break;
        }
    } while (choice != 0);
    List_Destroy(flag, schedule_node_t);
}

int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList)
{
    int x, y;
    printf("��������Ҫ���Ʊ���кţ�");
    scanf("%d", &x);
    printf("�����кţ�");
    scanf("%d", &y);
    printf("\n");
    ticket_list_t q;
    int cnt2 = 1;

    seat_list_t b;
    b = Seat_Srv_FindByRowCol(seatList, x, y); // �������У��ҵ���λ��Ϣ����buf������λ��Ϣ�����ڵ�

    if (b == NULL)
    {
        printf("����λ������!");
        return;
    }
    ticket_list_t flag;
    int i;
    flag = Ticket_Srv_FetchByID(b->data.id, tickList); // ������λid���ҵ�Ʊ����Ϣ����flag�洢Ʊ��Ϣ�����ڵ�
    // printf("tticket_id =%d\n",flag->data.id);

    if (flag == NULL)
    {
        printf("��Ʊ�����ڣ�\n");
        return;
    }
    else
    {
        printf("�ҵ���Ʊ��\n");
    }

    if (flag->data.status == 0)
    {
        printf("��Ʊ�ȴ��۳���\n");

        flag->data.status = 1;
        Ticket_Srv_Modify(&(flag->data));

        sale_t buf; // ���������Ʊ�����ۼ�¼

        long key = EntKey_Perst_GetNewKeys(SALE_KEY_NAME, 1); // ��ȡ����
        if (key <= 0)
            return 0;
        buf.id = key;
        printf("\n");
        printf("�������id");
        scanf("%d", &buf.user_id);

        buf.ticket_id = flag->data.id;
        // printf("tticket_id =%d\n",flag->data.id);
        // printf("tticket_id =%d\n",buf.ticket_id);

        buf.value == flag->data.price;

        struct tm *local;
        time_t t;
        t = time(&t);
        local = localtime(&t); // ��ǰ����
        printf("%d��%d��%d��\n", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday);
        buf.date.year = local->tm_year + 1900;
        buf.date.month = local->tm_mon + 1;
        buf.date.day = local->tm_mday;

        printf("%dʱ%d��%d��\n", local->tm_hour, local->tm_min, local->tm_sec);
        buf.time.hour = local->tm_hour;
        buf.time.minute = local->tm_min;
        buf.time.second = local->tm_sec;
        buf.type = 1; // ��Ʊ

        // printf("tticket_id =%d\n",buf.ticket_id);

        Sale_Srv_Add(&buf); // ��С���¬д���ļ���

        return 1;
    }
    else if (flag->data.status == 1)
    {
        printf("��Ʊ���۳���");
        return 0;
    }
    else
    {
        printf("��Ʊ�ѱ�Ԥ�������ɹ���");

        return 0;
    }
}

void Sale_UI_MgtEntry(void)
{
    play_list_t head;
    play_list_t pos;

    int i;

    Pagination_t paging;

    List_Init(head, play_node_t);
    paging.offset = 0;
    paging.pageSize = SIZE;
    int choice;

    //????????
    paging.totalRecords = Play_Srv_FetchAll(head); // head�������о�Ŀ����
    Paging_Locate_FirstPage(head, paging);
    system("clear");

    do
    {
        printf(
            "\n==================================================================\n");
        printf(
            "***************************** ��Ŀ��Ϣ ***************************\n");
        printf("%5s %15s %9s %5s %20s %10s\n", "ID", "��Ŀ����", "��Ʒ����",
               "ʱ��", "��ʼ->����", "Ʊ��");
        printf(
            "------------------------------------------------------------------\n");
        Paging_ViewPage_ForEach(head, paging, play_node_t, pos, i)
        {
            printf("%5d %8s %9s %5d %d/%d/%d->%d/%d/%d %5d\n", pos->data.id, pos->data.name, pos->data.area, pos->data.duration, pos->data.start_date.year, pos->data.start_date.month, pos->data.start_date.day, pos->data.end_date.year, pos->data.end_date.month, pos->data.end_date.day, pos->data.price);
        }
        printf(
            "------- ��:%2dҳ --------------------------------- ҳ�� :%2d/%2d ----\n",
            paging.totalRecords, Pageing_CurPage(paging),
            Pageing_TotalPages(paging));

        printf("\n\n\n\n");

        printf("-------------�ܼ�:%2d -------------- Page %2d/%2d --------------------\n",
               paging.totalRecords, Pageing_CurPage(paging), Pageing_TotalPages(paging));
        printf("*******************************************************************\n");
        printf("[1]��һҳ | [2]��һҳ | [3]����IDɸѡ�ݳ��ƻ� | [4]��������ɸѡ�ݳ��ƻ� | [0]����");
        printf("\n===================================================================\n");

        fflush(stdin);
        printf("�����룺");
        fflush(stdin);
        scanf("%d", &choice);
        fflush(stdin);
        system("clear");
        char name[64];
        switch (choice)
        {
            int id;
        case 3:
            system("clear");
            printf("������һ����Ŀid��");
            scanf("%d", &id);
            Sale_UI_ShowScheduler(id);
            break;

        case 4:

            system("clear");
            printf("������Ҫ��ѯ�ľ�Ŀ����:");
            scanf("%s", name);
            Schedule_UI_Query(name);
            break;

            // case 4:system("clear");
            // printf("������Ҫɾ�����û�����");
            // scanf("%s", name);
            // if (Account_UI_Delete(head,name)) {	//????????????
            // paging.totalRecords = Account_Srv_FetchAll(head);
            // List_Paging(head, paging, account_node_t);
            // }
            // break;
            // case 5:system("clear");
            // printf("������Ҫ��ѯ���û�����");
            // scanf("%s",name);
            // if(Account_UI_Query(head,name))
            // paging.totalRecords = Account_Srv_FetchAll(head);
            // List_Paging(head, paging, account_node_t)
            // ;
            // break;

        case 1:
            system("clear");
            if (!Pageing_IsFirstPage(paging))
            {
                Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
            }
            break;
        case 2:
            system("clear");
            if (!Pageing_IsLastPage(paging))
            {
                Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
            }
            break;
        case 4:

            system("clear");
            printf("������Ҫ��ѯ�ľ�Ŀ����:");
            scanf("%s", name);
            Schedule_UI_Query(name);
            break;
        }
    } while (choice != 0);

    // int x;
    // fflush(stdin);
    // printf("������Ҫ�˵�Ʊid��");
    // fflush(stdin);
    // scanf("%d", &x);
    // fflush(stdin);

    // ticket_list_t list;
    // List_Init(list,ticket_node_t);
    // Ticket_Srv_Make(list);//�ļ��л��Ʊ����

    // ticket_list_t flag;
    // flag=Ticket_Srv_FetchByTicketID(x,list);//��Ʊ������ ��Ʊid�ҵ���Ӧ�ڵ�
    // if(flag==NULL)
    // {
    // printf("��Ʊ�����ڣ�");
    // return;
    // }
    // if(flag->data.status==1)
    // {
    // flag->data.status==0;
    // Ticket_Srv_Modify(&(flag->data));//�޸�Ʊ��״̬

    // sale_t buf;
    // printf("�������ۼ�¼id��");//�������ۼ�¼
    // scanf("%d",&buf.id);
    // printf("�������id");
    // scanf("%d",&buf.user_id);
    // buf.ticket_id==flag->data.id;
    // buf.value==(flag->data.price)*(-1);
    // printf("�������ۼ�¼�����ڣ�");
    // scanf("%d/%d/%d",&buf.date.year,&buf.date.month,&buf.date.day);
    // printf("�������ۼ�¼��ʱ�䣺");
    // scanf("%d/%d/%d",&buf.time.hour,&buf.time.minute,&buf.time.second);
    // buf.type=-1;
    // Sale_Srv_Add(&buf);
    // printf("��Ʊ�ɹ�");

    // }
}

void Sale_UI_ShowTicket(int schedule_id)
{
    schedule_t schedule_buf;
    Schedule_Srv_FetchByID(schedule_id, &schedule_buf); // �����ݳ��ƻ�id���ҳ��ݳ��ƻ��Ľڵ���Ϣ �ݳ��ƻ����ɾ�Ŀid

    ticket_list_t buf; // buf������ĳ�ݳ��ƻ�������Ʊ Ʊ�����ݳ��ƻ�id
    List_Init(buf, ticket_node_t);
    ticket_list_t pos;

    Pagination_t paging;
    paging.offset = 0;
    paging.pageSize = SIZE;
    int i;
    int choice;

    seat_list_t flag; // flag�����ݳ��ƻ���������λ ��λ�����ݳ��ƻ�id
    List_Init(flag, seat_node_t);
    Seat_Srv_FetchByRoomID(flag, schedule_buf.studio_id); // ���ݾ�Ŀid�ҵ���λ����

    paging.totalRecords = Ticket_Srv_FetchBySchID(buf, schedule_id);
    Paging_Locate_FirstPage(buf, paging);

    do
    {

        printf(
            "\n=======================================================\n");
        printf(
            "********************** Ʊ����Ϣ ***********************\n");
        printf("%5s %5s %5s %5s %5s", "Ʊid", "�ݳ��ƻ�id", "��λid", "�۸�", "״̬\n");
        printf(
            "-------------------------------------------------------\n");
        Paging_ViewPage_ForEach(buf, paging, ticket_node_t, pos, i)
        {
            printf("%5d %5d %5d %5d %5d\n", pos->data.id, pos->data.schedule_id, pos->data.seat_id, pos->data.price, pos->data.status);
        }

        printf(
            "------- ��:%2d�� --------------------- ҳ�� :%2d/%2d ----\n",
            paging.totalRecords, Pageing_CurPage(paging),
            Pageing_TotalPages(paging));

        printf("\n\n\n\n");

        printf(
            "*******************************************************\n");
        printf("[1]��Ʊ|[0]����|[3]��һҳ|[4]��һҳ\n");
        printf("=======================================================\n");

        fflush(stdin);
        printf("�����룺");
        fflush(stdin);
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice)
        {
        case 1:
            system("clear");

            Sale_UI_SellTicket(buf, flag);

            break;

        case 3:
            system("clear");
            if (!Pageing_IsFirstPage(paging))
            {
                Paging_Locate_OffsetPage(buf, paging, -1, ticket_node_t);
            }
            break;
        case 4:
            system("clear");
            if (!Pageing_IsLastPage(paging))
            {
                Paging_Locate_OffsetPage(buf, paging, 1, ticket_node_t);
            }
            break;
        }
    } while (choice != 0);
    List_Destroy(flag, seat_node_t);
    List_Destroy(buf, ticket_node_t);
}

void Sale_UI_ShowScheduler1(int playID)
{
    play_t buf;
    int i;
    int choice;
    i = Play_Srv_FetchByID(playID, &buf);
    if (i == 0)
    {
        printf("�˾�Ŀid�����ڣ�");
        return;
    }

    schedule_list_t flag;
    List_Init(flag, schedule_node_t);
    Schedule_Srv_FetchByPlay(flag, playID); // flagΪ��Ŀid����Ӧ�������ݳ��ƻ�����

    schedule_list_t pos;

    Pagination_t paging;
    int len = 0;
    List_ForEach(flag, pos)
    {
        len++;
    }
    paging.offset = 0;
    paging.pageSize = SCHEDULE_PAGE_SIZE;
    paging.totalRecords = len;
    Paging_Locate_FirstPage(flag, paging);

    do
    {

        printf(
            "\n==================================================================\n");
        printf(
            "************************** �ݳ��ƻ���Ϣ **************************\n");
        printf("%8s %8s %8s %8s %8s %8s\n", "�ݳ��ƻ�ID", "��ӳ��ĿID", "�ݳ���ID",
               "��ӳ����", "��ӳʱ��", "��λ��");
        printf(
            "------------------------------------------------------------------\n");

        Paging_ViewPage_ForEach(flag, paging, schedule_node_t, pos, i)
        {
            printf("%8d %8d %8d %d/%d/%d %d/%d/%d %8d \n", pos->data.id,
                   pos->data.play_id, pos->data.studio_id, pos->data.date.year,
                   pos->data.date.month, pos->data.date.day, pos->data.time.hour,
                   pos->data.time.minute, pos->data.time.second, pos->data.seat_count);
        }

        printf(
            "------- ��:%2dҳ -------------------------------- ҳ�� :%2d/%2d ----\n",
            paging.totalRecords, Pageing_CurPage(paging),
            Pageing_TotalPages(paging));

        printf("\n\n\n\n");
        printf(
            "******************************************************************\n");

        printf("==================================================================\n");
        printf("[1]��һҳ | [2]��һҳ | [3]��ʾ�ݳ�Ʊ | [0]����\n");
        printf("==================================================================\n");

        fflush(stdin);
        printf("�����룺");
        fflush(stdin);
        scanf("%d", &choice);
        fflush(stdin);
        system("clear");

        int x;
        switch (choice)
        {
        case 3:
            system("clear");
            printf("�������ݳ��ƻ�id��");
            scanf("%d", &x);
            Sale_UI_ShowTicket1(x); // �����ݳ��ƻ�id����ȡƱ
            break;
        case 1:
            system("clear");
            if (!Pageing_IsFirstPage(paging))
            {
                Paging_Locate_OffsetPage(flag, paging, -1, schedule_node_t);
            }
            break;
        case 2:
            system("clear");
            if (!Pageing_IsLastPage(paging))
            {
                Paging_Locate_OffsetPage(flag, paging, 1, schedule_node_t);
            }
            break;
        }

    } while (choice != 0);
    List_Destroy(flag, schedule_node_t);
}

void Sale_UI_ShowTicket1(int schedule_id)
{
    schedule_t schedule_buf;
    Schedule_Srv_FetchByID(schedule_id, &schedule_buf); // �����ݳ��ƻ�id���ҳ��ݳ��ƻ��Ľڵ���Ϣ �ݳ��ƻ����ɾ�Ŀid

    ticket_list_t buf; // buf������ĳ�ݳ��ƻ�������Ʊ Ʊ�����ݳ��ƻ�id
    List_Init(buf, ticket_node_t);
    ticket_list_t pos;

    Pagination_t paging;
    paging.offset = 0;
    paging.pageSize = SIZE;
    int i;
    int choice;

    seat_list_t flag; // flag�����ݳ��ƻ���������λ ��λ�����ݳ��ƻ�id
    List_Init(flag, seat_node_t);
    Seat_Srv_FetchByRoomID(flag, schedule_buf.studio_id); // ���ݾ�Ŀid�ҵ���λ����

    paging.totalRecords = Ticket_Srv_FetchBySchID(buf, schedule_id);
    Paging_Locate_FirstPage(buf, paging);

    do
    {

        printf(
            "\n=======================================================\n");
        printf(
            "********************** Ʊ����Ϣ ***********************\n");
        printf("%5s %5s %5s %5s %5s", "Ʊid", "�ݳ��ƻ�id", "��λid", "�۸�", "״̬\n");
        printf(
            "-------------------------------------------------------\n");
        Paging_ViewPage_ForEach(buf, paging, ticket_node_t, pos, i)
        {
            printf("%5d %5d %5d %5d %5d\n", pos->data.id, pos->data.schedule_id, pos->data.seat_id, pos->data.price, pos->data.status);
        }

        printf(
            "------- ��:%2d�� --------------------- ҳ�� :%2d/%2d ----\n",
            paging.totalRecords, Pageing_CurPage(paging),
            Pageing_TotalPages(paging));

        printf("\n\n\n\n");

        printf(
            "*******************************************************\n");
        printf("[1]��Ʊ |[0]����|[3]��һҳ|[4]��һҳ\n");
        printf("=======================================================\n");

        fflush(stdin);
        printf("�����룺");
        fflush(stdin);
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice)
        {
        case 1:
            system("clear");

            Sale_UI_SellTicket1(buf, flag);

            break;

        case 3:
            system("clear");
            if (!Pageing_IsFirstPage(paging))
            {
                Paging_Locate_OffsetPage(buf, paging, -1, ticket_node_t);
            }
            break;
        case 4:
            system("clear");
            if (!Pageing_IsLastPage(paging))
            {
                Paging_Locate_OffsetPage(buf, paging, 1, ticket_node_t);
            }
            break;
        }
    } while (choice != 0);
    List_Destroy(flag, seat_node_t);
    List_Destroy(buf, ticket_node_t);
}

int Sale_UI_SellTicket1(ticket_list_t tickList, seat_list_t seatList)
{
    int x;
    fflush(stdin);
    printf("������Ҫ�˵�Ʊid��");
    fflush(stdin);
    scanf("%d", &x);
    fflush(stdin);

    ticket_list_t flag;
    flag = Ticket_Srv_FetchByTicketID(x, tickList); // ��Ʊ������ ��Ʊid�ҵ���Ӧ�ڵ�

    if (flag == NULL)
    {
        printf("��Ʊ�����ڣ�\n");
        return;
    }
    else
    {
        printf("�ҵ���Ʊ��\n");
    }

    if (flag->data.status == 1)
    {
        printf("��Ʊ�����ˣ�\n");

        flag->data.status = 0;
        Ticket_Srv_Modify(&(flag->data));

        sale_t buf; // ���������Ʊ�����ۼ�¼

        long key = EntKey_Perst_GetNewKeys(SALE_KEY_NAME, 1); // ��ȡ����
        if (key <= 0)
            return 0;
        buf.id = key;

        printf("�������id");
        scanf("%d", &buf.user_id);
        buf.ticket_id == flag->data.id;
        buf.value == flag->data.price;

        struct tm *local;
        time_t t;
        t = time(&t);
        local = localtime(&t); // ��ǰ����
        printf("%d��%d��%d��\n", local->tm_year + 1900, local->tm_mon + 1, local->tm_mday);
        buf.date.year = local->tm_year + 1900;
        buf.date.month = local->tm_mon + 1;
        buf.date.day = local->tm_mday;

        printf("%dʱ%d��%d��\n", local->tm_hour, local->tm_min, local->tm_sec);
        buf.time.hour = local->tm_hour;
        buf.time.minute = local->tm_min;
        buf.time.second = local->tm_sec;

        // printf("�������ۼ�¼�����ڣ�");
        // scanf("%d/%d/%d",&buf.date.year,&buf.date.month,&buf.date.day);
        // printf("�������ۼ�¼��ʱ�䣺");
        // scanf("%d/%d/%d",&buf.time.hour,&buf.time.minute,&buf.time.second);

        buf.type = -1; // ��Ʊ

        Sale_Srv_Add(&buf); // ��С���¬д���ļ���

        return 1;
    }
    else
    {
        printf("��Ʊδ�����򣬲����ˣ�");

        return 0;
    }
}

void Sale_UI_ShowTicketBypic(int schedule_id)
{
    schedule_t schedule_buf;
    Schedule_Srv_FetchByID(schedule_id, &schedule_buf); // �����ݳ��ƻ�id���ҳ��ݳ��ƻ��Ľڵ���Ϣ �ݳ��ƻ����ɾ�Ŀid

    studio_t buf_studio;
    Studio_Srv_FetchByID(schedule_buf.studio_id, &buf_studio);
    ticket_list_t buf; // buf������ĳ�ݳ��ƻ�������Ʊ Ʊ�����ݳ��ƻ�id
    List_Init(buf, ticket_node_t);
    ticket_list_t pos;

    Pagination_t paging;
    paging.offset = 0;
    paging.pageSize = SIZE;
    int i;
    int choice;

    seat_list_t flag; // flag�����ݳ��ƻ���������λ ��λ�����ݳ��ƻ�id
    List_Init(flag, seat_node_t);
    Seat_Srv_FetchByRoomID(flag, schedule_buf.studio_id); // ���ݾ�Ŀid�ҵ���λ����

    paging.totalRecords = Ticket_Srv_FetchBySchID(buf, schedule_id);
    Paging_Locate_FirstPage(buf, paging);

    {
        seat_list_t p;
        int flag2 = 0;
        printf("\n===== #���� +���� ' '��λ������/��=====\n\n");
        for (int i = 1; i <= buf_studio.rowsCount; i++)
        {
            printf("��%2d�� ", i);
            for (int j = 1; j <= buf_studio.colsCount; j++)
            {
                flag2 = 0;
                List_ForEach(flag, p) // ��λ����
                {
                    ticket_list_t tic_tmp;
                    tic_tmp = Ticket_Srv_FetchBySeatID(buf, p->data.id);
                    if (p->data.row == i && p->data.column == j)
                    {
                        // printf("1");
                        if (tic_tmp != NULL && tic_tmp->data.status == 1)
                            printf("+ ");
                        else
                            printf("# ");
                        // printf("%c ",Seat_UI_Status2Char(p->data.status));
                        flag2 = 1;
                        break;
                    }
                }
                if (flag2 == 0)
                    printf(" ");
            }
            printf("\n");
        }

        printf(
            "*******************************************************\n");
        printf("[1]��Ʊ|[0]����|[3]��һҳ|[4]��һҳ\n");
        printf("=======================================================\n");

        fflush(stdin);
        printf("�����룺");
        fflush(stdin);
        scanf("%d", &choice);
        fflush(stdin);

        switch (choice)
        {
        case 1:
            system("clear");

            Sale_UI_SellTicket(buf, flag);

            break;

        case 3:
            system("clear");
            if (!Pageing_IsFirstPage(paging))
            {
                Paging_Locate_OffsetPage(buf, paging, -1, ticket_node_t);
            }
            break;
        case 4:
            system("clear");
            if (!Pageing_IsLastPage(paging))
            {
                Paging_Locate_OffsetPage(buf, paging, 1, ticket_node_t);
            }
            break;
        }
    }
    while (choice != 0)
        ;
    List_Destroy(flag, seat_node_t);
    List_Destroy(buf, ticket_node_t);
}


void Sale_UI_ShowScheduler(int playID)
{
	play_t buf;
	int i;
	int choice;
	i=Play_Srv_FetchByID(playID,&buf);
	if(i==0)
	{
		printf("�˾�Ŀid�����ڣ�");
		return;
	}

	schedule_list_t flag;
	List_Init(flag, schedule_node_t);
	Schedule_Srv_FetchByPlay(flag,playID); //flagΪ��Ŀid����Ӧ�������ݳ��ƻ�����
	
	schedule_list_t pos;
	
	Pagination_t paging;
	int len = 0;
	List_ForEach(flag,pos)
	{
		len++;
	}
	paging.offset = 0;
	paging.pageSize = SCHEDULE_PAGE_SIZE;
	paging.totalRecords = len;
	Paging_Locate_FirstPage(flag, paging);

	
	do {

		printf(
				"\n==================================================================\n");
		printf(
				"************************** �ݳ��ƻ���Ϣ **************************\n");
		printf("%8s %8s  %8s  %8s  %8s %8s\n", "�ݳ��ƻ�ID", "��ӳ��ĿID", "�ݳ���ID",
				"��ӳ����", "��ӳʱ��","��λ��");
		printf(
				"------------------------------------------------------------------\n");
		
		Paging_ViewPage_ForEach(flag, paging, schedule_node_t, pos, i){
			printf("%8d %8d  %8d  %d/%d/%d  %d/%d/%d %8d \n", pos->data.id,
					pos->data.play_id, pos->data.studio_id, pos->data.date.year,
					pos->data.date.month,pos->data.date.day,pos->data.time.hour,
					pos->data.time.minute,pos->data.time.second,pos->data.seat_count);}

		printf(
				"------- ��:%2dҳ -------------------------------- ҳ�� :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        printf("\n\n\n\n"); 
        printf(
				"******************************************************************\n");

		printf("==================================================================\n");
		printf("[1]��һҳ       [2]��һҳ      [3]�б���ʾ�ݳ�Ʊ   \n[4]ͼ����ʾ�ݳ�Ʊ              [0]����\n");
		printf("==================================================================\n");
		
		fflush(stdin);
		printf("�����룺");
		fflush(stdin);
		scanf("%d", &choice);
		fflush(stdin);
		system("clear");
		
		
		int x;
		switch (choice) {
			case 3:
				system("clear");
				printf("�������ݳ��ƻ�id��");
				scanf("%d",&x);
				Sale_UI_ShowTicket(x);//�����ݳ��ƻ�id����ȡƱ
				break;
			case 4:
				system("clear");
				printf("�������ݳ��ƻ�id��");
				scanf("%d",&x);
				Sale_UI_ShowTicketBypic(x);//�����ݳ��ƻ�id����ȡƱ
				break;
			case 1:
				system("clear");
				if (!Pageing_IsFirstPage(paging)) {
					Paging_Locate_OffsetPage(flag, paging, -1, schedule_node_t);
				}
				break;
			case 2:
				system("clear");
				if (!Pageing_IsLastPage(paging)) {
					Paging_Locate_OffsetPage(flag, paging, 1, schedule_node_t);
				}
				break;
		}
	}while(choice!=0);
	List_Destroy(flag, schedule_node_t);
}



int Sale_UI_SellTicket(ticket_list_t tickList, seat_list_t seatList){
	int x,y;
	printf("��������Ҫ���Ʊ���кţ�");
	scanf("%d",&x);
	printf("�����кţ�");
	scanf("%d",&y);
	printf("\n");
	ticket_list_t q;
	int cnt2 = 1;


	seat_list_t b;
	b=Seat_Srv_FindByRowCol(seatList,x,y);//�������У��ҵ���λ��Ϣ����buf������λ��Ϣ�����ڵ�

	if(b == NULL) 
	{
		printf("����λ������!");
		return;
	}
	ticket_list_t flag;
	int i;
	flag=Ticket_Srv_FetchByID(b->data.id,tickList);//������λid���ҵ�Ʊ����Ϣ����flag�洢Ʊ��Ϣ�����ڵ�
	// printf("tticket_id =%d\n",flag->data.id);

	if(flag == NULL){
		printf("��Ʊ�����ڣ�\n");
		return;
	}
	else
	{
		printf("�ҵ���Ʊ��\n");
	}
	
	
	if(flag->data.status==0)
	{
		printf("��Ʊ�ȴ��۳���\n");

		flag->data.status=1;
		Ticket_Srv_Modify(&(flag->data));
		
		sale_t buf;//���������Ʊ�����ۼ�¼

		
		long key = EntKey_Perst_GetNewKeys(SALE_KEY_NAME, 1); //��ȡ����
		if(key<=0)			
			return 0;
		buf.id = key;	
		printf("\n");
		printf("�������id");
		scanf("%d",&buf.user_id);

		buf.ticket_id=flag->data.id;
		// printf("tticket_id =%d\n",flag->data.id);
		// printf("tticket_id =%d\n",buf.ticket_id);

		buf.value==flag->data.price;

		struct tm *local;
		time_t t;
		t=time(&t);
		local=localtime(&t);  //��ǰ����
		printf("%d��%d��%d��\n",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
		buf.date.year=local->tm_year+1900;
		buf.date.month=local->tm_mon+1;
		buf.date.day=local->tm_mday;

		printf("%dʱ%d��%d��\n",local->tm_hour,local->tm_min,local->tm_sec);
		buf.time.hour=local->tm_hour;
		buf.time.minute=local->tm_min;
		buf.time.second=local->tm_sec;
		buf.type=1;//��Ʊ

	// printf("tticket_id =%d\n",buf.ticket_id);
	
		Sale_Srv_Add(&buf);//��С���¬д���ļ���


		return 1;
	}
	else if(flag->data.status==1)
	{
		printf("��Ʊ���۳���");
		return 0;
	}
	else
	{
		printf("��Ʊ�ѱ�Ԥ�������ɹ���");

		return 0;
	}
}




void Sale_UI_MgtEntry(void)
{
	play_list_t head;
	play_list_t pos;
	
	int i;
	

	Pagination_t paging;

	List_Init(head, play_node_t);
	paging.offset = 0;
	paging.pageSize = SIZE;
	int choice;

	//????????
	paging.totalRecords = Play_Srv_FetchAll(head);//head�������о�Ŀ����
	Paging_Locate_FirstPage(head, paging);
	system("clear");
	

	do {
		printf(
				"\n==================================================================\n");
		printf(
				"***************************** ��Ŀ��Ϣ ***************************\n");
		printf("%5s %15s  %9s  %5s  %20s     %10s\n", "ID", "��Ŀ����", "��Ʒ����",
				"ʱ��", "��ʼ->����","Ʊ��");
		printf(
				"------------------------------------------------------------------\n");
		Paging_ViewPage_ForEach(head, paging, play_node_t, pos, i)
        {
			printf("%5d %8s  %9s  %5d  %d/%d/%d->%d/%d/%d  %5d\n", pos->data.id,pos->data.name,pos->data.area,pos->data.duration
            ,pos->data.start_date.year,pos->data.start_date.month,pos->data.start_date.day,pos->data.end_date.year,pos->data.end_date.month,pos->data.end_date.day,pos->data.price);
		}
		printf(
				"------- ��:%2dҳ --------------------------------- ҳ�� :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        
        
        printf("\n\n\n\n"); 
		

		printf("-------------�ܼ�:%2d -------------- Page %2d/%2d --------------------\n",
				paging.totalRecords, Pageing_CurPage(paging),Pageing_TotalPages(paging));
		printf("*******************************************************************\n");
		printf("[1]��һҳ  |   [2]��һҳ    |  [3]����IDɸѡ�ݳ��ƻ�  | [4]��������ɸѡ�ݳ��ƻ�  |   [0]����");
		printf("\n===================================================================\n");

		fflush(stdin);
		printf("�����룺");
		fflush(stdin);
		scanf("%d", &choice);
		fflush(stdin);
		system("clear");
		char name[64];
		switch (choice)
		 {
			int id;
			case 3:system("clear");
			printf("������һ����Ŀid��");
			scanf("%d",&id);
			Sale_UI_ShowScheduler(id); 
			break;
		
			case 4:
			
            system("clear");
			printf("������Ҫ��ѯ�ľ�Ŀ����:");
			scanf("%s", name);
			Schedule_UI_Query(name);
			break;

		// case 4:system("clear");
		// 	printf("������Ҫɾ�����û�����");
		// 	scanf("%s", name);
		// 	if (Account_UI_Delete(head,name)) {	//????????????
		// 		paging.totalRecords = Account_Srv_FetchAll(head);
		// 		List_Paging(head, paging, account_node_t);
		// 	}
			// break;
		// case 5:system("clear");
		// 	printf("������Ҫ��ѯ���û�����");
		// 	scanf("%s",name);
		// 	if(Account_UI_Query(head,name))
		// 	paging.totalRecords = Account_Srv_FetchAll(head);
		// 	List_Paging(head, paging, account_node_t)
		// 	;
		// 	break;


		case 1:system("clear");
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, -1, play_node_t);
			}
			break;
		case 2:system("clear");
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(head, paging, 1, play_node_t);
			}
			break;
		 }
	} while (choice != 0);
	//??????????
	//List_Destroy(head, sale_node_t);

}
void Sale_UI_ShowTicket(int schedule_id)
{
	schedule_t schedule_buf;
	Schedule_Srv_FetchByID(schedule_id,&schedule_buf);//�����ݳ��ƻ�id���ҳ��ݳ��ƻ��Ľڵ���Ϣ  �ݳ��ƻ����ɾ�Ŀid


	ticket_list_t buf;//buf������ĳ�ݳ��ƻ�������Ʊ      Ʊ�����ݳ��ƻ�id
	List_Init(buf,ticket_node_t);
	ticket_list_t pos;

	Pagination_t paging;
	paging.offset = 0;
	paging.pageSize = SIZE;
	int i;
	int choice;

	seat_list_t flag;//flag�����ݳ��ƻ���������λ      ��λ�����ݳ��ƻ�id
	List_Init(flag,seat_node_t);
	Seat_Srv_FetchByRoomID(flag,schedule_buf.studio_id);//���ݾ�Ŀid�ҵ���λ����

	
	paging.totalRecords=Ticket_Srv_FetchBySchID(buf,schedule_id);
	Paging_Locate_FirstPage(buf,paging);

	do {
		
		printf(
				"\n=======================================================\n");
		printf(
				"********************** Ʊ����Ϣ ***********************\n");
		printf("%5s  %5s  %5s %5s %5s","Ʊid","�ݳ��ƻ�id","��λid","�۸�","״̬\n");
		printf(
				"-------------------------------------------------------\n");
		Paging_ViewPage_ForEach(buf, paging, ticket_node_t, pos, i){
				printf("%5d  %5d  %5d  %5d  %5d\n",pos->data.id,pos->data.schedule_id,pos->data.seat_id,pos->data.price,pos->data.status);			
		}
	

		printf(
				"------- ��:%2d�� --------------------- ҳ�� :%2d/%2d ----\n",
				paging.totalRecords, Pageing_CurPage(paging),
				Pageing_TotalPages(paging));
		
        
        
        printf("\n\n\n\n"); 
        
        printf(
				"*******************************************************\n");
		printf("[1]��Ʊ|[0]����|[3]��һҳ|[4]��һҳ\n");
		printf("=======================================================\n");
		
		

		fflush(stdin);
		printf("�����룺");
		fflush(stdin);
		scanf("%d", &choice);
		fflush(stdin);

		switch(choice)
		{
			case 1:
			system("clear");
			
			Sale_UI_SellTicket(buf,flag);	
			
			break;

			case 3:system("clear");
			if (!Pageing_IsFirstPage(paging)) {
				Paging_Locate_OffsetPage(buf, paging, -1, ticket_node_t);
			}
			break;
			case 4:system("clear");
			if (!Pageing_IsLastPage(paging)) {
				Paging_Locate_OffsetPage(buf, paging, 1, ticket_node_t);
			}
			break;
		}
	}while(choice!=0);
	List_Destroy(flag, seat_node_t);
	List_Destroy(buf, ticket_node_t);



}



