### 编程练习
10. **编写一个函数，把两个数组中相对应的元素相加，然后把结果储存到第 3 个数组中。也就是说，如果数组1中包含的值是2、4、5、8，数组2中包含的值是1、0、4、6，那么该函数把3、4、9、14赋给第3个数组。函数接受3个数组名和一个数组大小。在一个简单的程序中测试该函数。**
```c
void addArray(int a[],int b[],int c[],int lenth)
{
    for(int i=0;i<lenth;i++)
    {
        c[i]=a[i]+b[i];
    }
}
```
11. **编写一个程序，声明一个int类型的3×5二维数组，并用合适的值初始化它。该程序打印数组中的值，然后各值翻倍（即是原值的2倍），并显示出各元素的新值。编写一个函数显示数组的内容，再编写一个函数把各元素的值翻倍。这两个函数都以函数名和行数作为参数。**
```c
void showArray(int a[3][5])
{
    for(int i=0;i<3;i++)
    {
        for(int k=0;k<5;k++)
        {
            printf("%d ",a[i][k]);
        }
    }
}
void douArray(int a[3][5])
{
    for(int i=0;i<3;i++)
    {
        for(int k=0;k<5;k++)
        {
            a[i][k]=2*a[i][k];
        }
    }
}
```
13.   **编写一个程序，提示用户输入3组数，每组数包含5个double类型的数（假设用户都正确地响应，不会输入非数值数据）。该程序应完成下列任务。**
```
a.把用户输入的数据储存在3×5的数组中
b.计算每组（5个）数据的平均值
c.计算所有数据的平均值
d.找出这15个数据中的最大值
e.打印结果
```
**每个任务都要用单独的函数来完成（使用传统C处理数组的方式）。完成任务b，要编写一个计算并返回一维数组平均值的函数，利用循环调用该函数3次。对于处理其他任务的函数，应该把整个数组作为参数，完成任务c和d的函数应把结果返回主调函数。**
```c
#include<stdio.h>
void get(double a[][5])
{
    printf("请输入数值:");
    for(int i=0;i<3;i++)
    {
        for(int k=0;k<5;k++)
        {
            scanf("%lf",&a[i][k]);
        }
    }
    printf("完成!");
}
void average(double a[][5])
{
    double sum=0;
    for(int i=0;i<3;i++)
    {
        sum=0;
        for(int k=0;k<5;k++)
        {
            sum+=a[i][k];
        }
        printf("%lf  ",sum/5);
    }
}
void averageall(double a[][5])
{
    double sum;
    for(int i=0;i<3;i++)
    {
        for(int k=0;k<5;k++)
        {
            sum+=a[i][k];
        }
    }
    printf("\n%lf",sum/15);
}
void findmax(double a[][5])
{
    double max=a[0][0];
    for(int i=0;i<3;i++)
    {
        for(int k=0;k<5;k++)
        {
            max=max>a[i][k]?max:a[i][k];
        }
    }
    printf("\n最大值为:%lf\n",max);
}
void print(double a[][5])
{
    for(int i=0;i<3;i++)
    {
        for(int k=0;k<5;k++)
        {
            printf("%lf ",a[i][k]);
        }
    }
}
int main(void)
{
    double a[3][5];
    get(a);
    average(a);
    averageall(a);
    findmax(a);
    print(a);
    return 0;
}
```
14.   **以变长数组作为函数形参，完成编程练习13**
```c
#include<stdio.h>
void get(int b,int c,double a[b][c])
{
    printf("请输入数值:");
    for(int i=0;i<b;i++)
    {
        for(int k=0;k<c;k++)
        {
            scanf("%lf",&a[i][k]);
        }
    }
    printf("完成!");
}
void average(int b,int c,double a[b][c])
{
    double sum=0;
    for(int i=0;i<b;i++)
    {
        sum=0;
        for(int k=0;k<c;k++)
        {
            sum+=a[i][k];
        }
        printf("%lf  ",sum/c);
    }
}
void averageall(int b,int c,double a[b][c])
{
    double sum;
    for(int i=0;i<b;i++)
    {
        for(int k=0;k<c;k++)
        {
            sum+=a[i][k];
        }
    }
    printf("\n%lf",sum/b/c);
}
void findmax(int b,int c,double a[b][c])
{
    double max=a[0][0];
    for(int i=0;i<b;i++)
    {
        for(int k=0;k<c;k++)
        {
            max=max>a[i][k]?max:a[i][k];
        }
    }
    printf("\n最大值为:%lf\n",max);
}
void print(int b,int c,double a[b][c])
{
    for(int i=0;i<b;i++)
    {
        for(int k=0;k<c;k++)
        {
            printf("%lf ",a[i][k]);
        }
    }
}
int main(void)
{
    int b,c;
    printf("请输入需要储存数组的行列(行,列):");
    scanf("%d,%d",&b,&c);
    double a[b][c];
    get(b,c,a);
    average(b,c,a);
    averageall(b,c,a);
    findmax(b,c,a);
    print(b,c,a);
    return 0;
}
```
