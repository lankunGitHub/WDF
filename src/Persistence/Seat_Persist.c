/*
* Copyright(C), 2007-2008, XUPT Univ.
* ������ţ�TTMS_UC_02	 
* File name: Seat.h	  
* Description : ������λ�����־û���	
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015��4��22��	
*/

#include "Seat_Persist.h"
#include "../Service/Seat.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>

static const char SEAT_DATA_FILE[] = "Seat.dat";
static const char SEAT_DATA_TEMP_FILE[] = "SeatTmp.dat";

//���Ӷ���������ʶ����
static const char SEAT_KEY_NAME[] = "Seat";

/*
�������ܣ��������ļ�������һ������λ���ݡ�
����˵����dataΪseat_t����ָ�룬��ʾ��Ҫ���ӵ���λ���ݽ��?
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���������λ�ı�־��?
*/ 
int Seat_Perst_Insert(seat_t *data) {   
	assert(NULL!=data);
	return 0;
}

/*
��ʶ����TTMS_SCU_Seat_Perst_InsertBatch
�������ܣ��������ļ�������һ����λ���ݡ�
����˵����listΪseat_list_t���ͣ���ʾ��Ҫ���ӵ�һ����λ������ͷָ�롣
�� �� ֵ�����ͣ���ʾ�ɹ�����һ����λ�ĸ�����
*/
int Seat_Perst_InsertBatch(seat_list_t list) {
	seat_node_t *p;
	assert(NULL!=list);

	return 0;
}

/*
��ʶ����TTMS_SCU_Seat_Perst_Update
�������ܣ��������ļ��и���һ����λ���ݡ�
����˵����dataΪseat_t����ָ�룬��ʾ��Ҫ���µ���λ���ݽ��?
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���������λ�ı�־��?
*/
int Seat_Perst_Update(const seat_t *seatdata) {
	assert(NULL!=seatdata);
	return 0;

}

/*
ʶ����TTMS_SCU_Seat_Perst_DelByID
�������ܣ����ڴ��ļ���ɾ��һ����λ�����ݡ�
����˵��������IDΪ���ͣ���ʾ��Ҫɾ������λID�� 
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�ɾ������λ�ı�־��?
*/
int Seat_Perst_DeleteByID(int ID) {
	
	return 0;
}

/*
��ʶ����TTMS_SCU_Seat_Perst_DelAllByID
�������ܣ����ݱ�����ڴ��ļ���ɾ����λ���ݡ�?
����˵��������roomIDΪ���ͣ���ʾ�ݳ���ID�� 
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�ɾ������λ�ı�־��?
*/ 
int Seat_Perst_DeleteAllByRoomID(int roomID) {
	if(rename(SEAT_DATA_FILE,SEAT_DATA_TEMP_FILE) == -1)
	{
		printf("Can't open the file : SEAT_DATA_FILE\n");
		return -1;
	}
	FILE *fpSour, *fpTarg;
	fpSour = fopen(SEAT_DATA_TEMP_FILE, "rb");
	if(fpSour == NULL)
	{
		printf("Can't open the file : SEAT_DATA_TEMP_FILE\n");
		return -1;
	}
	fpTarg = fopen(SEAT_DATA_FILE, "wb");
	if ( NULL == fpTarg ) {
		printf("Cannot open file %s!\n", SEAT_DATA_TEMP_FILE);
		return -1;
	}


	seat_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(seat_t), 1, fpSour)) {
			if (roomID == buf.roomID) {
				found = 1;
				continue;
			}
			fwrite(&buf, sizeof(seat_t), 1, fpTarg);
		}
	}
	fclose(fpTarg);
	fclose(fpSour);
	remove(SEAT_DATA_TEMP_FILE);
	return found;
	return 0;
}

/*
��ʶ����TTMS_SCU_Studio_Perst_SelByID
�������ܣ����ڴ��ļ�������һ����λ�����ݡ�
����˵������һ������IDΪ���ͣ���ʾ��Ҫ�������ݵ���λID���ڶ�������bufΪseat_tָ�룬ָ��������λ���ݵ�ָ�롣
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���������λ�ı�־��?
*/
int Seat_Perst_SelectByID(int ID, seat_t *buf) {
	
	return 0;
}

/*
��ʶ����TTMS_SCU_Seat_Perst_SelAll
�������ܣ����ڴ��ļ�������������λ���ݡ�
����˵����listΪseat_list_t���ͣ���ʾ��Ҫ�������λ����ͷָ��?
�� �� ֵ�����ͣ��ɹ�������λ�ĸ�����
*/
int Seat_Perst_SelectAll(seat_list_t list) {
	
	return 0;
}

/*
��ʶ����TTMS_SCU_Seat_Perst_SelByRoomID
�������ܣ��������ļ��и����ݳ���ID����������λ���ݡ�
����˵������һ������listΪseat_list_t���ͣ���ʾ��Ҫ�������λ����ͷָ��?�ڶ�������roomIDΪ���ͣ���ʾ�ݳ���ID��
�� �� ֵ�����ͣ���ʾ�ɹ��������ݳ�����λ�ĸ�����
*/
int Seat_Perst_SelectByRoomID(seat_list_t list, int roomID) {

	return 0;
}
