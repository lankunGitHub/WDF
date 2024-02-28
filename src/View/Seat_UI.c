/*
* Copyright(C), 2007-2008, XUPT Univ.	 
* ������ţ�TTMS_UC_02
* File name: Seat_UI.c			  
* Description : ������λ���������?	
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
	
	return "#";
}

/*
��ʶ����TTMS_SCU_Seat_UI_C2S
�������ܣ�����������Ż�ȡ��λ״�?��
����˵����statusCharΪ�ַ��ͣ���ʾ������λ��������š�?
�� �� ֵ��seat_status_t���ͣ���ʾ��λ��״̬��
*/
inline seat_status_t Seat_UI_Char2Status(char statusChar) {
	
	return SEAT_NONE;
}

/*
��ʶ����TTMS_SCU_Seat_UI_MgtEnt
�������ܣ�����������λ����ں�������ʾ��ǰ����λ���ݣ����ṩ��λ�������ӡ��޸ġ�ɾ�����ܲ�������ڡ�
����˵����roomIDΪ���ͣ�����Ҫ������λ���ݳ���ID��
�� �� ֵ���ޡ�
*/ 
void Seat_UI_MgtEntry(int roomID) {

}

/*
ʶ����TTMS_SCU_Seat_UI_Add
�������ܣ���������һ���µ���λ���ݡ�
����˵������һ������listΪseat_list_t����ָ�룬ָ����λ����ͷָ�룬
         �ڶ�������rowsCountΪ���ͣ���ʾ��λ�����кţ�����������colsCountΪ���ͣ���ʾ��λ�����кš�
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���������λ�ı�־��?
*/
int Seat_UI_Add(seat_list_t list, int roomID, int row, int column) {  //����һ����λ

	return 0;
}

/*
��ʶ����TTMS_SCU_Seat_UI_Mod 
�������ܣ������޸�һ����λ���ݡ�
����˵������һ������listΪseat_list_t����ָ�룬ָ����λ����ͷָ�룬�ڶ�������rowsCountΪ���ͣ���ʾ��λ�����кţ�����������colsCountΪ���ͣ���ʾ��λ�����кš�
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ��޸�����λ�ı�־��?
*/
int Seat_UI_Modify(seat_list_t list, int row, int column) {
	if(!(seat_node_t* temp = Seat_Srv_FindByRowCol(list,row,column)))
	{
		printf("The seat does not exist!\nPress [Enter] key to return!\n");
		getchar();
		return 0;
	}
	printf("\n=======================================================\n");
	printf("****************  Update Projection Seat  ****************\n");
	printf("-------------------------------------------------------\n");
	printf("seat ID:%d     ", temp->id);
	printf("roomID:%d      ", temp->roomID);
	printf("seat status:%d  [0]NONE | [1] GOOD | [9] BROKEN\n",temp->seat_status_t);
	fflush();
	switch(temp->seat_status_t)
	{
		case 0:
			printf("Input Your Choice  [1] GOOD | [9] BROKEN: ");
			scanf("%d",&temp->seat_status_t);
			break;
		case 1:
			printf("Input Your Choice  [0] NONE | [9] BROKEN: ");
			scanf("%d",&temp->seat_status_t);
			break;
		case 9:
			printf("Input Your Choice  [1] GOOD | [0] NONE: ");
			scanf("%d",&temp->seat_status_t);
			break;
		default :
			printf("Input Wrong Status, Try Again");
	};

}

/*
��ʶ����TTMS_SCU_Seat_UI_Del
�������ܣ�����ɾ��һ����λ�����ݡ�
����˵������һ������listΪseat_list_t����ָ�룬ָ����λ����ͷָ�룬�ڶ�������rowsCountΪ���ͣ���ʾ��λ�����кţ�����������colsCountΪ���ͣ���ʾ��λ�����кš�
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�ɾ������λ�ı�־��?
*/
int Seat_UI_Delete(seat_list_t list, int row, int column) {

	return 0;

}

