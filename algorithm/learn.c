#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#define MAXSIZE 20
typedef int ElemType
//线性表抽象数据定义
/*
Data（有固定的前后驱元素）
Operation
    InitList(*L)       //初始化空的线性表
    ListEmpty(L)       //检查线性表是否为空
    ClearList(*L)      //清空线性表
    LocateElem(L,e)    //寻找元素1,若存在返回位置
    GetElem(L,i,*e)    //将第i个元素赋值给e
*/



//线性表顺序储存结构(数组)
/*
typedef struct
{
    ElemType data[MAXSIZE];
    int lenth;
}SqList;
*/
//插入，删除
/*
*/