/*
* Copyright(C), 2007-2008, XUPT Univ.	 
* ������ţ�TTMS_UC_02
* File name: Seat_UI.c			  
* Description : ������λ���������	
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015��4��22��	
*/

#include "Seat_UI.h"
#include "../Service/Seat.h"

#include "../Service/Studio.h"
#include "../Common/List.h"
#include <stdio.h>

/*
��ʶ����TTMS_SCU_Seat_UI_S2C 
�������ܣ�������λ״̬��ȡ������ʾ���š�
����˵����statusΪseat_status_t���ͣ���ʾ��λ״̬��
�� �� ֵ���ַ��ͣ���ʾ��λ�Ľ�����ʾ���š�
*/
inline char Seat_UI_Status2Char(seat_status_t status) {
    if(status == 0)
    return '0';//�п�λ 
    else if(status == 1)
	return '#';//���� 
	else return '*';//���� 
}

/*
��ʶ����TTMS_SCU_Seat_UI_C2S
�������ܣ�����������Ż�ȡ��λ״̬��
����˵����statusCharΪ�ַ��ͣ���ʾ������λ��������š�
�� �� ֵ��seat_status_t���ͣ���ʾ��λ��״̬��
*/
inline seat_status_t Seat_UI_Char2Status(char statusChar) {
	if(statusChar == '0')
	return SEAT_NONE;
	else if(statusChar == '#')
	return SEAT_GOOD;
	else return SEAT_BROKEN;
}

/*
��ʶ����TTMS_SCU_Seat_UI_MgtEnt
�������ܣ�����������λ����ں�������ʾ��ǰ����λ���ݣ����ṩ��λ������ӡ��޸ġ�ɾ�����ܲ�������ڡ�
����˵����roomIDΪ���ͣ�����Ҫ������λ���ݳ���ID��
�� �� ֵ���ޡ�         ����= 
*/ 
int Seat_UI_MgtEntry(int roomID) {
	 	studio_t buf;
	 	int choice2;
			int choice ;
	if(Studio_Srv_FetchByID(roomID,&buf))
	{//�ݳ�������
		seat_list_t list;
		List_Init(list,seat_node_t);
		if(!Seat_Srv_FetchByRoomID(list,roomID))//�ж���λ�Ƿ����
		{//��������λ
			
			buf.seatsCount = Seat_Srv_RoomInit(list,roomID,buf.rowsCount,buf.colsCount);
			Studio_Srv_Modify(&buf);
			printf("��λ��ʼ�����!\n");
			printf("��[ENTER]����\n");
			setbuf(stdin,NULL);
			getchar();
		}
		else
		{
			
			
			
				seat_node_t *p;
				int flag = 0;
				int i,j;
				for( i = 1;i<=buf.rowsCount;i++)
				{
					printf("��%2d��   ",i);
					for(j = 1;j<=buf.colsCount;j++)
					{
						flag = 0;
						List_ForEach(list,p)
						{
								if(p->data.row == i && p->data.column == j) 
								{
									printf("%c ",Seat_UI_Status2Char(p->data.status));
									flag = 1;
									break;
								}
						}
						if(flag == 0) printf("  ");
						}
					printf("\n");
				}

						             
						
						
							printf(
									"******************************************************************\n");
							printf(
									"[1]�����λ | [2]ɾ����λ |  [3]�޸���λ | [0]�����ϲ�");
							printf(
									"\n\n\n\n==================================================================\n");
							printf("��������Ҫ���еĲ���:");
							setbuf(stdin,NULL);
							scanf("%d",&choice);


							switch (choice)
							{
										case 1:
										{
												int row,col;
												printf("������Ҫ��ӵ���λ����:\n");
											
												do
												{
													do{
													printf("�к�(<=%d):",buf.rowsCount);
													scanf("%d",&row);
													printf("�к�(<=%d):",buf.colsCount);
													scanf("%d",&col);
													if(row > buf.rowsCount || col > buf.colsCount)
													printf("���벻�Ϸ�!\n");
													
												}while(row > buf.rowsCount || col > buf.colsCount);
											

												choice2 = Seat_UI_Add(list,roomID,row,col);
												
										
												
												}
												while(choice2==1);
												//int Seat_UI_Modify(seat_list_t list, int row, int column)
												
												// char map[buf.rowsCount+5][buf.colsCount+5];
												// Seat_Srv_map(list,(char*)map,buf.colsCount);
												// //printf("�����λ!\n");
												// for(int  i =1;i<=buf.rowsCount;i++)
												// {
												// 	printf("��%d�� ",i);
												// 	for(int j = 1;j<=buf.colsCount;j++)
												// 	{
												// 		printf("%c ",*((char *)map+i*buf.colsCount+j));
												// 	}
												// 	printf("\n");
												// }
												//system("clear");
												break;
										}


									case 2:
								
										{
											int row,col;
											printf("������Ҫɾ������λ����:\n");
											do
												{
													
													printf("�к�(<=%d):",buf.rowsCount);
													scanf("%d",&row);
													printf("�к�(<=%d):",buf.colsCount);
													scanf("%d",&col);
													if(row > buf.rowsCount || col > buf.colsCount)
														printf("���벻�Ϸ�!\n");
												}while(row > buf.rowsCount || col > buf.colsCount);

											Seat_UI_Delete(list,row,col);//int Seat_UI_Modify(seat_list_t list, int row, int column)
											// char map[buf.rowsCount+5][buf.colsCount+5];
											// Seat_Srv_map(list,(char*)map,buf.colsCount);
											// //printf("�����λ!\n");
											// for(int  i =1;i<=buf.rowsCount;i++)
											// {
											// 	printf("��%d�� ",i);
											// 	for(int j = 1;j<=buf.colsCount;j++)
											// 	{
											// 		printf("%c ",*((char *)map+i*buf.colsCount+j));
											// 	}
											// 	printf("\n");
											// }
											getchar();
											
											break;
										}
										


									case 3:
										{
											int row,col;
											printf("������Ҫ�������λ����:\n");
											do
												{
												
													printf("�к�(<=%d):",buf.rowsCount);
													scanf("%d",&row);
													printf("�к�(<=%d):",buf.colsCount);
													scanf("%d",&col);
														if(row > buf.rowsCount || col > buf.colsCount)
														printf("���벻�Ϸ�!\n");
												}while(row > buf.rowsCount || col > buf.colsCount);

											Seat_UI_Modify(list,row,col);//int Seat_UI_Modify(seat_list_t list, int row, int column)
											// char map[buf.rowsCount+5][buf.colsCount+5];
											// Seat_Srv_map(list,(char*)map,buf.colsCount);
											// //printf("�����λ!\n");
											// for(int  i =1;i<=buf.rowsCount;i++)
											// {
											// 	printf("��%d�� ",i);
											// 	for(int j = 1;j<=buf.colsCount;j++)
											// 	{
											// 		printf("%c ",*((char *)map+i*buf.colsCount+j));
											// 	}
											// 	printf("\n");
											// }
											// //system("clear");
											break;
										}
									case 0:
										break;
										



									default:
										printf("������������������!\n");
										break;
							}
							
							Seat_Srv_FetchByRoomID(list,roomID);
						    
						
						

					
		}
		
		
	}
	else
	{
		printf("�ݳ���������!\n");
		printf("��[ENTER]�����ϲ�");
		setbuf(stdin,NULL);
		getchar();
		system("clear");
		return ;
	}
	return choice;
}

int Seat_UI_Add(seat_list_t list, int roomID, int row, int column) 
{  
    int choice,choice2;
		seat_list_t p = Seat_Srv_FindByRowCol(list,row,column);
		if(p != NULL)
		{
			printf("��λ�Ѿ�����!\n");
			printf("����[ENTRE]�����ϲ�!\n");
			setbuf(stdin,NULL);
			getchar();
			return 0;
		}
		else
		{//��λ�����ڿ������
			seat_t data;
			data.roomID = roomID;
			data.row = row; 
			data.column = column;
			printf("��������λ״̬([0]���� | [1] �� | [9] ��):");
			scanf("%d",&data.status);
			if(Seat_Srv_Add(&data))
			{
				printf("��ӳɹ�!\n");
				printf("[1] ������� | [0]�����ϲ�");
				scanf("%d",&choice2);
			}
			else printf("���ʧ��!\n");
			// printf("����[ENTRE]�����ϲ�!\n");
			// setbuf(stdin,NULL);
			// getchar();
			
			
			
		}
			

	return 	choice2;
	
}




/*
��ʶ����TTMS_SCU_Seat_UI_Mod 
�������ܣ������޸�һ����λ���ݡ�
����˵������һ������listΪseat_list_t����ָ�룬ָ����λ����ͷָ�룬�ڶ�������rowsCountΪ���ͣ���ʾ��λ�����кţ�����������colsCountΪ���ͣ���ʾ��λ�����кš�
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ��޸�����λ�ı�־��
*/
int Seat_UI_Modify(seat_list_t list, int row, int column) {

	int flag = 0;
	seat_list_t p = Seat_Srv_FindByRowCol(list, row, column);
	if( p == NULL)
	{
		printf("����λ������!\n");
	}
	else
	{
				seat_t rec;
				printf("������Ҫ�޸ĵ���λ״̬([0]���� | [1] �� | [9] ��):");
				setbuf(stdout,NULL);
				setbuf(stdin,NULL);
				scanf("%d",&rec.status);
				rec.column = p->data.column;
				rec.roomID = p->data.roomID;
				rec.row = p->data.row;
				// printf("status = %d\n",rec.status);
				Seat_Srv_Modify(&rec);
	}
	
	return 0;

}

/*
��ʶ����TTMS_SCU_Seat_UI_Del
�������ܣ�����ɾ��һ����λ�����ݡ�
����˵������һ������listΪseat_list_t����ָ�룬ָ����λ����ͷָ�룬�ڶ�������rowsCountΪ���ͣ���ʾ��λ�����кţ�����������colsCountΪ���ͣ���ʾ��λ�����кš�
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�ɾ������λ�ı�־��
*/
int Seat_UI_Delete(seat_list_t list, int row, int column)//ָ��ͷָ�룬�У��� 
{
	int rtn = 0;//�ж��Ƿ�ɹ� 
	seat_list_t p = Seat_Srv_FindByRowCol(list,row,column);//��ȡ��λ
	if(p != NULL)
	{
		Seat_Srv_DeleteByID(p->data.id);
		printf(
		"�ɹ�ɾ������λ\n");
		rtn = 1;
	}
	else
	{
		printf("��λ������\n");
	}
	//������ 
	return rtn;

}

