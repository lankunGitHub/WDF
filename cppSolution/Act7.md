### 编程练习
7. **编写一个程序，提示用户输入一周工作的小时数，然后打印工资总额、税金和净收入。做如下假设：**
```
a.基本工资 = 10:00美元/小时
b.加班（超过40小时） = 1.5倍的时间
c.税率： 前300美元为15%
续150美元为20%
余下的为25%
```
用#define定义符号常量。不用在意是否符合当前的税法。
```c
#include<stdio.h>
#define SALARY 10
int main(void)
{
    float hour;
    double money,tax,get;
    printf("请输入一周工作时间：");
    scanf("%f",&hour);
    while(hour>0)
    {
    if(hour>40)  
    {
        hour*=1.5;
        money=hour*SALARY;
        tax=(money-400)*0.25+65;
        get=money-tax;
    }
    else if(hour<=30)  
    {
        money=hour*SALARY;
        tax=money*.15;
        get=money-tax;
    }
    else if(hour>30&&hour<=40)
    {
        money=hour*SALARY;
        tax=(money-300)*0.20+45;
        get=money-tax;
    }
    printf("salary:%.2lf money:%.2lf tax:%.2lf\n",get,money,tax);
    printf("请输入一周工作时间：(0 to quit)");
    scanf("%f",hour);
    }
}
```
9. **编写一个程序，只接受正整数输入，然后显示所有小于或等于该数的素数。**
```c
#include<stdio.h>
#include<math.h>
int main(void)
{
    int n,flag=1;
    scanf("%d",&n);
    for(int i=2;i<=n;i++)
    {
        flag=1;
        for(int k=2;k<sqrt(n)+1;k++)
        {
            if(i%k==0)  flag=0;
        }
        if(flag)  printf("%d\n",i);
    }
}
```
10. **1988年的美国联邦税收计划是近代最简单的税收方案。它分为4个类别，每个类别有两个等级。**
**下面是该税收计划的摘要（美元数为应征税的收入）：**
```
单身              17850美元按15%计，超出部分按28%计
户主              23900美元按15%计，超出部分按28%计
已婚，共有         29750美元按15%计，超出部分按28%计
已婚，离异         14875美元按15%计，超出部分按28%计
```
**例如，一位工资为20000美元的单身纳税人，应缴纳税费0.15×17850+0.28×（20000−17850）美元。编写一个程序，让用户指定缴纳税金的种类和应纳税收入，然后计算税金。程序应通过循环让用户可以多次输入。**
```c
#include<stdio.h>
int main(void)
{
    int a=1;
    float salary,tax;
    
    while(a)
    {
    printf("请输入当前状态(1单身;2户主;3已婚,共有;4已婚,离异,0停止):");
    scanf("%d",&a);
    printf("请输入你的工资：");
    scanf("%f",&salary);
    switch(a)
    {
        case 1:
        if(salary<=17850)
        {
            tax=salary*0.15;
        }
        else
        {
            tax=(salary-17850)*0.28+17850*0.15;
        }
        break;
        case 2:
        if(salary<=23900)
        {
            tax=salary*0.15;
        }
        else
        {
            tax=(salary-23900)*0.28+23900*0.15;
        }
        break;
        case 3:
        if(salary<=29750)
        {
            tax=salary*0.15;
        }
        else
        {
            tax=(salary-29750)*0.28+29750*0.15;
        }
        break;
        case 4:
        if(salary<=14875)
        {
            tax=salary*0.15;
        }
        else
        {
            tax=(salary-14875)*0.28+14875*0.15;
        }
        break;
        default:
        break;
    };
    printf("您需要缴纳税金：%.2f\n",tax);
    }
}
```
11. **ABC 邮购杂货店出售的洋蓟售价为 2.05 美元/磅，甜菜售价为 1.15美元/磅，胡萝卜售价为 1.09美元/磅。在添加运费之前，100美元的订单有5%的打折优惠。少于或等于5磅的订单收取6.5美元的运费和包装费，5磅～20磅的订单收取14美元的运费和包装费，超过20磅的订单在14美元的基础上每续重1磅增加0.5美元。编写一个程序，在循环中用switch语句实现用户输入不同的字母时有不同的响应，即输入a的响应是让用户输入洋蓟的磅数，b是甜菜的磅数，c是胡萝卜的磅数，q 是退出订购。程序要记录累计的量。即，如果用户输入 4 磅的甜菜，然后输入 5磅的甜菜，程序应报告9磅的甜菜。然后，该程序要计算货物总价、折扣（如果有的话）、运费和包装费。随后，程序应显示所有的购买信息：物品售价、订购的重量（单位：磅）、订购的蔬菜费用、订单的总费用、折扣（如果有的话）、运费和包装费，以及所有的费用总额。**
```c
#include<stdio.h>
#define G 2.05
#define S 1.15
#define C 1.09
int main(void)
{
    int kind;
    float a,b;
    while(1)
    {
        printf("请输入订购蔬菜种类(1洋蓟;2甜菜;3胡萝卜;q停止)");
        scanf("%d",&kind);
        switch(kind)
        {
            case 1:
            printf("请输入订购数量：");
            scanf("%f",&b);
            if(b<=5)   a=G*b+6.5;
            else if(b>5&&b<=20)  a=G*b+14;
            else if(b>20)   a=G*b+14+(b-20)*0.5;
            break;
            case 2:
            printf("请输入订购数量：");
            scanf("%f",&b);
            if(b<=5)   a=S*b+6.5;
            else if(b>5&&b<=20)  a=S*b+14;
            else if(b>20)   a=S*b+14+(b-20)*0.5;
            break;
            case 3:
            printf("请输入订购数量：");
            scanf("%f",&b);
            if(b<=5)   a=S*b+6.5;
            else if(b>5&&b<=20)  a=S*b+14;
            else if(b>20)   a=S*b+14+(b-20)*0.5;
            break;
            default:
            return 0;
        };
        printf("支付费用为：%.2f\n",a);
    }
}
```