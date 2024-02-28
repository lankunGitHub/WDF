### 编程练习
6. **编写并测试一个函数，该函数以3个double变量的地址作为参数，把最小值放入第1个函数，中间值放入第2个变量，最大值放入第3个变量。**
```c
#include<stdio.h>
void exchange(double *a,double *b,double *c)
{
    double d,e,f;
    d=(*a>*b?*a:*b)>*c?(*a>*b?*a:*b):*c;
    e=(*a>*b?*b:*a)>*c?(*a>*b?*b:*a):*c;
    f=(*a>*b?*b:*a)>*c?*c:(*a>*b?*b:*a);
    *a=d;
    *b=e;
    *c=f;
}

int main(void)
{
    double a,b,c;
    printf("请依次输入a,b,c:(格式为:a b c)");
    scanf("%lf %lf %lf",&a,&b,&c);
    exchange(&a,&b,&c);
    printf("a=%.2lf b=%.2lf c=%.2lf \n",a,b,c);
}
```
7. 编写一个函数，从标准输入中读取字符，直到遇到文件结尾。程序要报告每个字符是否是字母。如果是，还要报告该字母在字母表中的数值位置。例如，c和C在字母表中的位置都是3。合并一个函数，以一个字符作为参数，如果该字符是一个字母则返回一个数值位置，否则返回-1。
```c
#include<stdio.h>
void get(char ch)
{
    while((ch=getchar())!=EOF)
    {
        if(ch>='a'&&ch<='z')  printf("%d ",ch-'a'+1);
        else if(ch>='A'&&ch<='Z')  printf("%d ",ch-'A'-1);
        else printf("-1 ")
    }
}
```
8. **第6章的程序清单6.20中，power()函数返回一个double类型数的正整数次幂。改进该函数，使其能正确计算负幂。另外，函数要处理0的任何次幂都为0，任何数的0次幂都为1（函数应报告0的0次幂未定义，因此把该值处理为1）。要使用一个循环，并在程序中测试该函数。**
```c
double power(void)
{
    double a;
    int b;
    double sum=1;
    do
    {
    
    printf("Please input a number(0 to quit):");
    scanf("%lf",&a);
    if(a==0)  break;
    printf("Please enter the times:");
    scanf("%d",&b);
    if(b==0)  return 0;
    else if(b>0)
    {
        for(int i=1;i<=b;i++)
        {
            sum*=a;
        }
    }
    else if(b<0)
    {
        b=-b;
        for(int i=1;i<=b;i++)
        {
            a=1/a;
            sum*=a;
        }
    }
    printf("The result is:%lf",sum);
    }while(1);
    return 1;  //如果只是一次计算就不需要循环，直接return sum
}
```
11. **编写并测试Fibonacci()函数，该函数用循环代替递归计算斐波那契数。**
```c
void Fibonacci()
{
    int a=1,b=1,c,d;
    printf("请输入需要斐波那契数的项数:");
    scanf("%d",&d);
    for(int i=1;i<=d;i++)
    {
        c=a+b;
        printf("%d ",c);
        a=b;
        b=c;
    }
}
```