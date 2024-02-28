### 编程练习
5. **编写一个程序，生成100个1～10范围内的随机数，并以降序排列（可以把第11章的排序算法稍加改动，便可用于整数排序，这里仅对整数排序）。**
```c
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int main(void)
{
    intt a[10];
    srand((unsigned)time(NULL));
    for(int i=0;i<10;i++)
    {
        a[i]=rand()%10+1;
    }
    for(int i=0;i<9;i++)
    {
        for(int k=0;k<9-i;k++)
        {
            if(a[k]>a[k+1])
            {
                int t=a[k];
                a[k]=a[k+1];
                a[k+1]=t;
            }
        }
    }
}
```
6. **编写一个程序，生成1000个1～10范围内的随机数。不用保存或打印这些数字，仅打印每个数出现的次数。用 10 个不同的种子值运行，生成的数字出现的次数是否相同？可以使用本章自定义的函数或ANSI C的rand()和srand()函数，它们的格式相同。这是一个测试特定随机数生成器随机性的方法。**
```c
#include<stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    short hash[10]={0};
    srand((unsigned)time(NULL));
    for(int i=0;i<1000;i++)
    {
        int a=rand()%10+1;
        hash[a]++;
    }
    for(int i=0;i<10;i++)
    {
        printf("%hd ",hash[i]);
    }
}
```
8. **下面是程序的一部分：**
```c
// pe12-8.c
#include <stdio.h>
int * make_array(int elem, int val);
void show_array(const int ar [], int n);
int main(void)
{
int * pa;
int size;
int value;
printf("Enter the number of elements: ");
while (scanf("%d", &size) == 1 && size > 0)
{
printf("Enter the initialization value: ");
scanf("%d", &value);
pa = make_array(size, value);
if (pa)
{
show_array(pa, size);
free(pa);
}
printf("Enter the number of elements (<1 to quit): ");
}
printf("Done.\n");
return 0;
}
```
**提供make_array()和show_array()函数的定义，完成该程序。make_array()函数接受两个参数，第1个参数是int类型数组的元素个数，第2个参数是要赋给每个元素的值。该函数调用malloc()创建一个大小合适的数组，将其每个元素设置为指定的值，并返回一个指向该数组的指针。show_array()函数显示数组的内容，一行显示8个数。**
```c
#include<stdlib.h>
int * make_array(int elem, int val)
{
    int *array=(int *)malloc(sizeof(int)*elem);
    for(int i=0;i<elem;i++)
    {
        *(array+i)=val;
    }
    return array;
}
void show_array(const int ar [], int n)
{
    for(int i=0;i<n;i++)
    {
        printf("%d",ar[i]);
         if((i+1)%8==0)  printf("\n");
    }
}
```
9. **编写一个符合以下描述的函数。首先，询问用户需要输入多少个单词。然后，接收用户输入的单词，并显示出来，使用malloc()并回答第1个问题（即要输入多少个单词），创建一个动态数组，该数组内含相应的指向char的指针（注意，由于数组的每个元素都是指向char的指针，所以用于储存malloc()返回值的指针应该是一个指向指针的指针，且它所指向的指针指945向char）。在读取字符串时，该程序应该把单词读入一个临时的char数组，使用malloc()分配足够的存储空间来储存单词，并把地址存入该指针数组（该数组中每个元素都是指向 char 的指针）。然后，从临时数组中把单词拷贝到动态分配的存储空间中。因此，有一个字符指针数组，每个指针都指向一个对象，该象的大小正好能容纳被储存的特定单词。下面是该程序的一个运行示例：**
```
How many words do you wish to enter? 5
Enter 5 words now:
I enjoyed doing this exerise
Here are your words:
I
enjoyed
doing
this
exercise
```
```c
#include<stdio.h>
#include<stdlib.h>
#define SIZE 20

int main(void)
{
    int n;
    do
    {
        printf("How many words do you wish to enter?(0 to quit)");
        scanf("%d",&n);
        printf("Enter %d words now:\n",n);
        char (*a)[SIZE]=(char*)malloc(sizeof(char)*n*SIZE);
        for(int i=0;i<n;i++)
        {
            scanf("%s",&a[i]);
            printf("%s ",a[i]);
        }
        printf("\n");
        printf("Here are your words:\n");
        for(int i=0;i<n;i++)
        {
            printf("%s\n",a[i]);
        }
        free(a);
    }while(n!=0);
}

```