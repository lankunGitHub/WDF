### 编程练习
8. **巨人航空公司的机群由 12 个座位的飞机组成。它每天飞行一个航班。根据下面的要求，编写一个座位预订程序。**
```
a.该程序使用一个内含 12 个结构的数组。每个结构中包括：一个成员
表示座位编号、一个成员表示座位是否已被预订、一个成员表示预订人的
名、一个成员表示预订人的姓。
b.该程序显示下面的菜单：
To choose a function, enter its letter label:
a) Show number of empty seats
b) Show list of empty seats
c) Show alphabetical list of seats
d) Assign a customer to a seat assignment
e) Delete a seat assignment
f) Quit
c.该程序能成功执行上面给出的菜单。选择d)和e)要提示用户进行额外输入，每个选项都能让用户中止输入。
d.执行特定程序后，该程序再次显示菜单，除非用户选择f)。
```
```c
#include<stdio.h>
 struct Seats
{
    int num;
    bool order;
    char firstName[20];
    char lastName[20];
};
int main(void)
{
    struct Seats seat[12];
    for(int i=0;i<12;i++)
    {
        seat[i].order=0;
        seat[i].num=i+1;
        seat[i].firstName[0]='\0';
        seat[i].lastName[0]='\0';
    }
    char a;
    int sum=0;
    int booknum;
    do
    {
        printf("To choose a function, enter its letter label:\na) Show number of empty seats\nb) Show list of empty seats\nc) Show alphabetical list of seats\nd) Assign a customer to a seat assignment\ne) Delete a seat assignment\nf) Quit\n");
        scanf("%c",&a);
        switch(a)
        {
            case 'a':
                for(int i=0;i<12;i++)
                {
                    if(seat[i].order==0)
                    {
                        sum++;
                    }
                }
                printf("%d",sum);
                sum=0;
                break;
            case 'b':
                for(int i=0;i<12;i++)
                {
                    if(seat[i].order==0)
                    {
                       printf("%d  ",seat[i].num);
                    }
                }
                break;
            case 'c':
                for(int i=0;i<11;i++)
                {
                    for(int k=0;k<11-i;k++)
                    {
                        if(seat[k].firstName[0]>seat[k+1].firstName[0])
                        {
                            struct Seats t;
                            t=seat[k];
                            seat[k]=seat[k+1];
                            seat[k+1]=seat[k];
                        }
                    }
                }
                for(int i=0;i<12;i++)
                {
                    if(seat[i].order==1)
                    {
                        printf("%s %s",seat[i].firstName,seat[i].lastName);
                    }
                }
                break;
            case 'd':
                printf("Assign a customer to a seat assignment:");
                scanf("%d",&booknum);
                seat[booknum].order=1;
                break;
            case 'e':
            printf("Delete a seat assignment");
                scanf("%d",&booknum);
                seat[booknum].order=0;
                break;
            case 'f':
                break;
        };
    } while (a!='f');
    
}
```
10. **编写一个程序，通过一个函数指针数组实现菜单。例如，选择菜单中的 a，将激活由该数组第 1个元素指向的函数。**
```c
void function1(char a);
void function2(char a);
void function3(char a);
 int mian(void)
 {
    void (*functionRun[3])(char a);
    functionRun[0]=function1;
    functionRun[1]=function2;
    functionRun[2]=function3;
    int a;
    do
    {
        printf(".....");
        scanf("%d",&a);
        switch(a)
        {
            /*....*/
        };
    } while (a!=' ');
    
 }
 ```
 11. **编写一个名为transform()的函数，接受4个参数：内含double类型数据的源数组名、内含double类型数据的目标数组名、一个表示数组元素个数的int类型参数、函数名（或等价的函数指针）。transform()函数应把指定函数应用于源数组中的每个元素，并把返回值储存在目标数组中。例如：transform(source, target, 100, sin);该声明会把target[0]设置为sin(source[0])，等等，共有100个元素。在一个程序中调用transform()4次，以测试该函数。分别使用math.h函数库中的两个函数以及自定义的两个函数作为参数。**
```c
#include<stdio.h>
#include<math.h>
void transform(double source[],double target[],int n,double (*function)(double))
{
    for(int i=0;i<n;i++)
    {
        target[i]=function(source[i]);
    }
}
```