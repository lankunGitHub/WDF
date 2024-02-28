/*
* Copyright(C), 2007-2008, XUPT Univ.	
* ������ţ�TTMS_UC_02 
* File name: Seat.c		  
* Description : ������λ����ҵ���߼���	
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015��4��22��	
*/

#include <stdlib.h>
#include "../Common/List.h"
#include "Seat.h"

/*
�������ܣ���������һ������λ���ݡ�
����˵����dataΪseat_t����ָ�룬��ʾ��Ҫ���ӵ���λ���ݽ��?
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���������λ�ı�־��?
*/
int Seat_Srv_Add(const seat_t *data){
	// �벹������
       return 0;
}

/*
�������ܣ�����������λ���ݡ�
����˵����listΪseat_list_t����ָ�룬��ʾ��Ҫ���ӵ�������λ�����γɵ�������
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�������������λ�ı�־��?
*/
int Seat_Srv_AddBatch(seat_list_t list){
	// �벹������
       return 0;
}

/*
�������ܣ������޸�һ����λ���ݡ�
����˵����dataΪseat_t����ָ�룬��ʾ��Ҫ�޸ĵ���λ���ݽ��?
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ��޸�����λ�ı�־��?
*/
int Seat_Srv_Modify(const seat_t *data){
	// �벹������
       return 0;
}

/*
�������ܣ�������λIDɾ��һ����λ��
����˵����IDΪ���ͣ���ʾ��Ҫɾ������λ���ݽ��?
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�ɾ������λ�ı�־��?
*/
int Seat_Srv_DeleteByID(int ID){
	// �벹������
       return 1;
}

/*
�������ܣ�������λID��ȡ��λ���ݡ�
����˵������һ������IDΪ���ͣ���ʾ��λID���ڶ�������bufΪseat_tָ�룬ָ�����ȡ����λ���ݽ�㡣
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���ȡ����λ�ı�־��?
*/
int Seat_Srv_FetchByID(int ID, seat_t *buf){
	// �벹������
       return 0;
}

/*
�������ܣ������ݳ���IDɾ��������λ��
����˵����roomIDΪ���ͣ���ʾ��Ҫɾ��������λ���ݳ���ID��
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�ɾ�����ݳ���������λ�ı�־��?
*/
inline int Seat_Srv_DeleteAllByRoomID(int roomID){
	// �벹������
       return 0;
}

/*
�������ܣ����ݸ����ݳ������С�������ʼ���ݳ�����������λ���ݣ�����ÿ����λ��㰴�в�����λ������?
����˵������һ������listΪseat_list_t����ָ�룬ָ����λ����ͷָ�룬�ڶ�������rowsCountΪ���ͣ���ʾ��λ�����кţ�����������colsCountΪ���ͣ���ʾ��λ�����кš�
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���ʼ�����ݳ�����������λ��?
*/
int Seat_Srv_FetchByRoomID(seat_list_t list, int roomID){
       // �벹������
       return 0;
       memset()
}

/*
�������ܣ������ݳ���ID��ø��ݳ�������Ч��λ��?
����˵������һ������listΪseat_list_t���ͣ���ʾ��ȡ������Ч��λ����ͷָ�룬�ڶ�������roomIDΪ���ͣ���ʾ��Ҫ��ȡ��Ч��λ���ݳ���ID��
�� �� ֵ�����ͣ���ʾ�ݳ�������Ч��λ������
*/
int Seat_Srv_FetchValidByRoomID(seat_list_t list, int roomID)
{
       // �벹������
       return 0;
}

/*
�������ܣ����ݸ����ݳ������С�������ʼ���ݳ�����������λ���ݣ�����ÿ����λ��㰴�в�����λ������?
����˵������һ������listΪseat_list_t����ָ�룬ָ����λ����ͷָ�룬�ڶ�������rowsCountΪ���ͣ���ʾ��λ�����кţ�����������colsCountΪ���ͣ���ʾ��λ�����кš�
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���ʼ�����ݳ�����������λ��?
*/
int Seat_Srv_RoomInit(seat_list_t list, int roomID, int rowsCount,int colsCount) {
       int count = 1;
	for(int i = 1;i <= rowsCount;i++)
       {
              for(int k = 1;k <= colsCount;k++)
              {
                     seat_list_t node = malloc(sizeof(seat_t));
                     if(node == NULL) return  -1;
                     node->data.column = k;
                     node->data.id = count++;
                     node->data.roomID = roomID;
                     node->data.row = rowsCount;
                     node->data.status = 1;
                     List_AddTail(list,node);
              }
       }
       return 0;
}

/*
�������ܣ�����λ����list����λ�кš��кŽ�������
����˵����listΪseat_list_t���ͣ���ʾ��������λ����ͷָ�롣
�� �� ֵ���ޡ�
*/
void Seat_Srv_SortSeatList(seat_list_t list) {
       // �벹������
}

/*
�������ܣ���һ����λ�����뵽���������λ�����С�?
����˵������һ������listΪseat_list_t���ͣ���ʾ�����������λ����ͷָ��?�ڶ�������nodeΪseat_node_tָ�룬��ʾ��Ҫ�������λ���ݽ�㡣
�� �� ֵ���ޡ�
*/
void Seat_Srv_AddToSoftedList(seat_list_t list, seat_node_t *node) {
       // �벹������
}

/*
�������ܣ�������λ���С��кŻ�ȡ��λ���ݡ�
����˵������һ������listΪseat_list_t���ͣ���ʾ��λ����ͷָ�룬
         �ڶ�������rowΪ���ͣ���ʾ����ȡ��λ���кţ�����������columnΪ���ͣ���ʾ����ȡ��λ���кš�
�� �� ֵ��Ϊseat_node_tָ�룬��ʾ��ȡ������λ���ݡ�
*/
seat_node_t * Seat_Srv_FindByRowCol(seat_list_t list, int row, int column) {
       // �벹������
       return NULL;
}

/*
�������ܣ�������λID�������л�ȡ��λ���ݡ�
����˵������һ������listΪseat_list_t���ͣ�ָ����λ�����������ڶ�������IDΪ���ͣ���ʾ��λID��
�� �� ֵ��seat_node_t���ͣ���ʾ��ȡ����λ���ݡ�
*/
seat_node_t * Seat_Srv_FindByID(seat_list_t list, int rowID) {
       // �벹������
       return NULL;
}
