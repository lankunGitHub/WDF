/*
* Copyright(C), 2007-2008, XUPT Univ.	 
* 用例编号：TTMS_UC_02
* File name: Seat_UI.c			  
* Description : 设置座位用例界面层	
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015年4月22日	
*/

#include "Seat_UI.h"
#include "../Service/Seat.h"

#include "../Service/Studio.h"
#include "../Common/List.h"
#include <stdio.h>

/*
表识符：TTMS_SCU_Seat_UI_S2C 
函数功能：根据座位状态获取界面显示符号。
参数说明：status为seat_status_t类型，表示座位状态。
返 回 值：字符型，表示座位的界面显示符号。
*/
inline char Seat_UI_Status2Char(seat_status_t status) {
    if(status == 0)
    return '0';//有空位 
    else if(status == 1)
	return '#';//有座 
	else return '*';//损坏座 
}

/*
标识符：TTMS_SCU_Seat_UI_C2S
函数功能：根据输入符号获取座位状态。
参数说明：statusChar为字符型，表示设置座位的输入符号。
返 回 值：seat_status_t类型，表示座位的状态。
*/
inline seat_status_t Seat_UI_Char2Status(char statusChar) {
	if(statusChar == '0')
	return SEAT_NONE;
	else if(statusChar == '#')
	return SEAT_GOOD;
	else return SEAT_BROKEN;
}

/*
标识符：TTMS_SCU_Seat_UI_MgtEnt
函数功能：界面层管理座位的入口函数，显示当前的座位数据，并提供座位数据添加、修改、删除功能操作的入口。
参数说明：roomID为整型，是需要设置座位的演出厅ID。
返 回 值：无。         待定= 
*/ 
int Seat_UI_MgtEntry(int roomID) {
	 	studio_t buf;
	 	int choice2;
			int choice ;
	if(Studio_Srv_FetchByID(roomID,&buf))
	{//演出厅存在
		seat_list_t list;
		List_Init(list,seat_node_t);
		if(!Seat_Srv_FetchByRoomID(list,roomID))//判断座位是否存在
		{//不存在座位
			
			buf.seatsCount = Seat_Srv_RoomInit(list,roomID,buf.rowsCount,buf.colsCount);
			Studio_Srv_Modify(&buf);
			printf("座位初始化完成!\n");
			printf("按[ENTER]继续\n");
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
					printf("第%2d行   ",i);
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
									"[1]添加座位 | [2]删除座位 |  [3]修改座位 | [0]返回上层");
							printf(
									"\n\n\n\n==================================================================\n");
							printf("请输入您要进行的操作:");
							setbuf(stdin,NULL);
							scanf("%d",&choice);


							switch (choice)
							{
										case 1:
										{
												int row,col;
												printf("请输入要添加的座位坐标:\n");
											
												do
												{
													do{
													printf("行号(<=%d):",buf.rowsCount);
													scanf("%d",&row);
													printf("列号(<=%d):",buf.colsCount);
													scanf("%d",&col);
													if(row > buf.rowsCount || col > buf.colsCount)
													printf("输入不合法!\n");
													
												}while(row > buf.rowsCount || col > buf.colsCount);
											

												choice2 = Seat_UI_Add(list,roomID,row,col);
												
										
												
												}
												while(choice2==1);
												//int Seat_UI_Modify(seat_list_t list, int row, int column)
												
												// char map[buf.rowsCount+5][buf.colsCount+5];
												// Seat_Srv_map(list,(char*)map,buf.colsCount);
												// //printf("输出座位!\n");
												// for(int  i =1;i<=buf.rowsCount;i++)
												// {
												// 	printf("第%d行 ",i);
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
											printf("请输入要删除的座位坐标:\n");
											do
												{
													
													printf("行号(<=%d):",buf.rowsCount);
													scanf("%d",&row);
													printf("列号(<=%d):",buf.colsCount);
													scanf("%d",&col);
													if(row > buf.rowsCount || col > buf.colsCount)
														printf("输入不合法!\n");
												}while(row > buf.rowsCount || col > buf.colsCount);

											Seat_UI_Delete(list,row,col);//int Seat_UI_Modify(seat_list_t list, int row, int column)
											// char map[buf.rowsCount+5][buf.colsCount+5];
											// Seat_Srv_map(list,(char*)map,buf.colsCount);
											// //printf("输出座位!\n");
											// for(int  i =1;i<=buf.rowsCount;i++)
											// {
											// 	printf("第%d行 ",i);
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
											printf("请输入要管理的座位坐标:\n");
											do
												{
												
													printf("行号(<=%d):",buf.rowsCount);
													scanf("%d",&row);
													printf("列号(<=%d):",buf.colsCount);
													scanf("%d",&col);
														if(row > buf.rowsCount || col > buf.colsCount)
														printf("输入不合法!\n");
												}while(row > buf.rowsCount || col > buf.colsCount);

											Seat_UI_Modify(list,row,col);//int Seat_UI_Modify(seat_list_t list, int row, int column)
											// char map[buf.rowsCount+5][buf.colsCount+5];
											// Seat_Srv_map(list,(char*)map,buf.colsCount);
											// //printf("输出座位!\n");
											// for(int  i =1;i<=buf.rowsCount;i++)
											// {
											// 	printf("第%d行 ",i);
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
										printf("输入有误，请重新输入!\n");
										break;
							}
							
							Seat_Srv_FetchByRoomID(list,roomID);
						    
						
						

					
		}
		
		
	}
	else
	{
		printf("演出厅不存在!\n");
		printf("按[ENTER]返回上层");
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
			printf("座位已经存在!\n");
			printf("按下[ENTRE]返回上层!\n");
			setbuf(stdin,NULL);
			getchar();
			return 0;
		}
		else
		{//座位不存在可以添加
			seat_t data;
			data.roomID = roomID;
			data.row = row; 
			data.column = column;
			printf("请输入座位状态([0]过道 | [1] 好 | [9] 损坏):");
			scanf("%d",&data.status);
			if(Seat_Srv_Add(&data))
			{
				printf("添加成功!\n");
				printf("[1] 继续添加 | [0]返回上层");
				scanf("%d",&choice2);
			}
			else printf("添加失败!\n");
			// printf("按下[ENTRE]返回上层!\n");
			// setbuf(stdin,NULL);
			// getchar();
			
			
			
		}
			

	return 	choice2;
	
}




/*
标识符：TTMS_SCU_Seat_UI_Mod 
函数功能：用于修改一个座位数据。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功修改了座位的标志。
*/
int Seat_UI_Modify(seat_list_t list, int row, int column) {

	int flag = 0;
	seat_list_t p = Seat_Srv_FindByRowCol(list, row, column);
	if( p == NULL)
	{
		printf("该座位不存在!\n");
	}
	else
	{
				seat_t rec;
				printf("请输入要修改的座位状态([0]过道 | [1] 好 | [9] 损坏):");
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
标识符：TTMS_SCU_Seat_UI_Del
函数功能：用于删除一个座位的数据。
参数说明：第一个参数list为seat_list_t类型指针，指向座位链表头指针，第二个参数rowsCount为整型，表示座位所在行号，第三个参数colsCount为整型，表示座位所在列号。
返 回 值：整型，表示是否成功删除了座位的标志。
*/
int Seat_UI_Delete(seat_list_t list, int row, int column)//指向头指针，行，列 
{
	int rtn = 0;//判断是否成功 
	seat_list_t p = Seat_Srv_FindByRowCol(list,row,column);//获取座位
	if(p != NULL)
	{
		Seat_Srv_DeleteByID(p->data.id);
		printf(
		"成功删除此座位\n");
		rtn = 1;
	}
	else
	{
		printf("座位不存在\n");
	}
	//简单制作 
	return rtn;

}

