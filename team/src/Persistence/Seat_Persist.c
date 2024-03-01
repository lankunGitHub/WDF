/*
* Copyright(C), 2007-2008, XUPT Univ.
* ������ţ�TTMS_UC_02	 
* File name: Seat.h	  
* Description : ������λ�����־û���	
* Author:   XUPT  		 
* Version:  v.1 	 
* Date: 	2015��4��22��	
*/
#include "EntityKey_Persist.h"
#include "Seat_Persist.h"
#include "../Service/Seat.h"
#include "../Common/List.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include <assert.h>

static const char SEAT_DATA_FILE[] = "Seat.dat";
static const char SEAT_DATA_TEMP_FILE[] = "SeatTmp.dat";

//��Ӷ���������ʶ����
static const char SEAT_KEY_NAME[] = "Seat";

/*
�������ܣ��������ļ������һ������λ���ݡ�
����˵����dataΪseat_t����ָ�룬��ʾ��Ҫ��ӵ���λ���ݽ�㡣
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ��������λ�ı�־��
*/ 
int Seat_Perst_Insert(seat_t *data) {   
    assert(NULL!=data);
	long key = EntKey_Perst_GetNewKeys(SEAT_KEY_NAME, 1); 
	if(key<=0)			
		return 0;
	data->id = key;	


	FILE *fp = fopen(SEAT_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) 
	{
		printf("Cannot open file %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	rtn = fwrite(data, sizeof(seat_t), 1, fp);

	fclose(fp);
	return rtn;
	}

/*
��ʶ����TTMS_SCU_Seat_Perst_InsertBatch
�������ܣ��������ļ������һ����λ���ݡ�
����˵����listΪseat_list_t���ͣ���ʾ��Ҫ��ӵ�һ����λ������ͷָ�롣
�� �� ֵ�����ͣ���ʾ�ɹ����һ����λ�ĸ�����
*/
int Seat_Perst_InsertBatch(seat_list_t list) {
	int rtn = 0;
	seat_node_t *p;
	assert(NULL!=list);

	int len = 0;
	List_ForEach(list,p)
	{
		len++;
	}
	int key = EntKey_Perst_GetNewKeys(SEAT_KEY_NAME,len);
	if(key <= 0) 
	{
		printf("��������ʧ��!\n");
		return 0;
	}
	else
	{
		FILE *fp = fopen(SEAT_DATA_FILE,"ab");
		if(fp == NULL) 
		{
			printf("���ļ�ʧ��%s",SEAT_DATA_FILE);
			return 0;
		}
		else
		{
			List_ForEach(list,p)
			{
				p->data.id = key++;
				fwrite(&p->data,sizeof(seat_t),1,fp);
				rtn++;
			}
		}
		fclose(fp);
		
		
	}
	
	return rtn;
}

/*
��ʶ����TTMS_SCU_Seat_Perst_Update
�������ܣ��������ļ��и���һ����λ���ݡ�
����˵����dataΪseat_t����ָ�룬��ʾ��Ҫ���µ���λ���ݽ�㡣
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���������λ�ı�־��
*/
int Seat_Perst_Update(seat_t *seatdata) {
	assert(NULL!=seatdata);
		FILE *fp = fopen(SEAT_DATA_FILE, "rb+");
	if (NULL == fp) {
		printf("Cannot open file %s!\n", SEAT_DATA_FILE);
		return 0;
	}
	//�鿴�Ƿ�ɲ� 
	seat_t buf;//��ӳ���ṹ���� 
	int found = 0;
	seatdata->id = (int)EntKey_Perst_GetNewKeys(SEAT_KEY_NAME, 1);//�����ţ��ѱ��� 
	while (!feof(fp)) {
		if (fread(&buf, sizeof(seat_t), 1, fp)) {
			if (buf.row == seatdata->row&&buf.column == seatdata->column)//�Ƿ�Ϊ������λ�� ,��������Ƿ���� 
			 {
				fseek(fp, -((int)sizeof(seat_t)), SEEK_CUR);//���ļ���ʱָ��λ��ָ������ṹ�ĳ�ʼλ�� 
				fwrite(seatdata, sizeof(seat_t), 1, fp);//��ȡ���� 
				found = 1;//�ɹ� 
				break;
			}

		}
	}
	fclose(fp);

	return found;
}/*
int Seat_Perst_Insert(seat_t *data) {   
    assert(NULL!=data);
	long key = EntKey_Perst_GetNewKeys(SEAT_KEY_NAME, 1); 
	if(key<=0)			
		return 0;
	data->id = key;	


	FILE *fp = fopen(SEAT_DATA_FILE, "ab");
	int rtn = 0;
	if (NULL == fp) 
	{
		printf("Cannot open file %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	rtn = fwrite(data, sizeof(seat_t), 1, fp);

	fclose(fp);
	return rtn;
	}
*/
/*

ʶ����TTMS_SCU_Seat_Perst_DelByID
�������ܣ����ڴ��ļ���ɾ��һ����λ�����ݡ�
����˵��������IDΪ���ͣ���ʾ��Ҫɾ������λID�� 
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�ɾ������λ�ı�־��
*/
int Seat_Perst_DeleteByID(int ID) {
	
if(rename(SEAT_DATA_FILE, SEAT_DATA_TEMP_FILE)<0){
		printf("Cannot open file %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(SEAT_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour ){
		printf("Cannot open file %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(SEAT_DATA_FILE, "wb");
	if ( NULL == fpTarg ) {
		printf("Cannot open file %s!\n", SEAT_DATA_TEMP_FILE);
		return 0;
	}


	seat_t buf;

	int found = 0;
	while (!feof(fpSour)) {
		if (fread(&buf, sizeof(seat_t), 1, fpSour)) {
			if (ID == buf.id) {
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
}

/*
��ʶ����TTMS_SCU_Seat_Perst_DelAllByID
�������ܣ����ݱ�����ڴ��ļ���ɾ����λ���ݡ�
����˵��������roomIDΪ���ͣ���ʾ�ݳ���ID�� 
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ�ɾ������λ�ı�־��
*/ 
int Seat_Perst_DeleteAllByRoomID(int roomID) {
	
	if(rename(SEAT_DATA_FILE, SEAT_DATA_TEMP_FILE)<0){
		printf("Cannot open file %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	FILE *fpSour, *fpTarg;
	fpSour = fopen(SEAT_DATA_TEMP_FILE, "rb");
	if (NULL == fpSour ){
		printf("Cannot open file %s!\n", SEAT_DATA_FILE);
		return 0;
	}

	fpTarg = fopen(SEAT_DATA_FILE, "wb");
	if ( NULL == fpTarg ) {
		printf("Cannot open file %s!\n", SEAT_DATA_TEMP_FILE);
		return 0;
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

	//?????????
	remove(SEAT_DATA_TEMP_FILE);
	return found;
}

/*
��ʶ����TTMS_SCU_Studio_Perst_SelByID
�������ܣ����ڴ��ļ�������һ����λ�����ݡ�
����˵������һ������IDΪ���ͣ���ʾ��Ҫ�������ݵ���λID���ڶ�������bufΪseat_tָ�룬ָ��������λ���ݵ�ָ�롣
�� �� ֵ�����ͣ���ʾ�Ƿ�ɹ���������λ�ı�־��
*/
int Seat_Perst_SelectByID(int ID, seat_t *buf) {
	
	assert(NULL!=buf);

	FILE *fp = fopen(SEAT_DATA_FILE, "rb");
	if (NULL == fp) {
		return 0;
	}

	seat_t data;
	int found = 0;

	while (!feof(fp)) {
		if (fread(&data, sizeof(seat_t), 1, fp)) {
			if (ID == data.id) {
				*buf = data;
				found = 1;
				break;
			};

		}
	}
	fclose(fp);

	return found;
}

/*
��ʶ����TTMS_SCU_Seat_Perst_SelAll
�������ܣ����ڴ��ļ�������������λ���ݡ�
����˵����listΪseat_list_t���ͣ���ʾ��Ҫ�������λ����ͷָ�롣
�� �� ֵ�����ͣ��ɹ�������λ�ĸ�����
*/
int Seat_Perst_SelectAll(seat_list_t list) {
	seat_node_t *newNode;//����˫������ 
	seat_t data;//������λ�ṹ 
	int recCount = 0;//�ж��Ƿ�ɹ������Լ�����ĸ��� 

	assert(NULL!=list);

	List_Free(list, seat_node_t);//�ͷ���������ݽڵ� 

	FILE *fp = fopen(SEAT_DATA_FILE, "rb");
	if (NULL == fp) { 
		return 0;
	}
 
	while (!feof(fp)) {
		if (fread(&data, sizeof(seat_t), 1, fp)) {
			newNode = (seat_node_t*) malloc(sizeof(seat_node_t));
			if (!newNode) {
				printf(
						"Warning, Memory OverFlow!!!\n Cannot Load more Data into memory!!!\n");
				break;
			}
			newNode->data = data;
			List_AddTail(list, newNode);
			recCount++;
		}
	}//�ļ�������ֹͣѭ�� 
	fclose(fp);
	return recCount;
}


/*
��ʶ����TTMS_SCU_Seat_Perst_SelByRoomID
�������ܣ��������ļ��и����ݳ���ID����������λ���ݡ�
����˵������һ������listΪseat_list_t���ͣ���ʾ��Ҫ�������λ����ͷָ�룬�ڶ�������roomIDΪ���ͣ���ʾ�ݳ���ID��
�� �� ֵ�����ͣ���ʾ�ɹ��������ݳ�����λ�ĸ�����
*/
int Seat_Perst_SelectByRoomID(seat_list_t list, int roomID) {
	  int recCount = 0;
	if(access(SEAT_DATA_FILE,F_OK) == -1)//�ļ�������
	{
		printf("SEAT_DATA_FILE�ļ�������\n");
		return 0;
	}
	else
	{
		seat_node_t *p ;
		p = (seat_list_t)malloc(sizeof(seat_node_t));
		FILE *fp = fopen(SEAT_DATA_FILE,"rb");
		seat_t q;
		while(1)
		{
				
				if(fread(&q,sizeof(seat_t),1,fp) < 1) break;
				if(q.roomID == roomID)
				{
					p->data = q;
					List_AddTail(list,p);
					recCount++;
				}
				else
				{
					free(p);
				}
				
				p = (seat_list_t)malloc(sizeof(seat_node_t));
		}



		fclose(fp);

		
	}
	return recCount;
}
