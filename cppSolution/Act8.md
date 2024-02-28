### 编程练习
4. **编写一个程序，在遇到EOF之前，把输入作为字符流读取。该程序要报告平均每个单词的字母数。不要把空白统计为单词的字母。实际上，标点符号也不应该统计，但是现在暂时不同考虑这么多（如果你比较在意这点，考虑使用ctype.h系列中的ispunct()函数）。**
```c
#include<stdio.h>
#include<string.h>
int main(void)
{
    float words=0,letters=0;
    char a;
    while((a=getchar())!=EOF)
    {
        if((a>='a'&&a<='z')||(a>='A'&&a<='Z'))  letters++;
        else    words++;
    }
    printf("%.0f\n",letters/words);
}
```
5. **修改程序清单8.4的猜数字程序，使用更智能的猜测策略。例如，程序最初猜50，询问用户是猜大了、猜小了还是猜对了。如果猜小了，那么下一次猜测的值应是50和100中值，也就是75。如果这次猜大了，那么下一次猜测的值应是50和75的中值，等等。使用二分查找（binary search）策略，如果用户没有欺骗程序，那么程序很快就会猜到正确的答案。**
```c
#include<stdio.h>
int main(void)
{
    int guess=50,a,b;
    printf("请输入一个1~100的数:");
    scanf("%d",&a);
    while(guess!=a)
    {
        printf("是不是%d(1猜小了;2猜大了)",guess);
        scanf("%d",&b);
        if(b==1)
        {
            guess/=2;
        }
        else if(b==2)
        {
            guess=50+guess/2;
        }
        
    }
    printf("num=%d",guess);

}
```
6. **修改程序清单8.8中的get_first()函数，让该函数返回读取的第1个非空白字符，并在一个简单的程序中测试。**
```c
#include<stdio.h>
char get_first(void)
{
    char ch;
    do
    {
        ch=getchar();
    }while(ch==' '||ch=='\n'||ch=='\t');
    return ch;
}
int main(void)
{
    char ch;
    ch=get_first(void);
    printf("%c\n",ch);
}
```
8. **编写一个程序，显示一个提供加法、减法、乘法、除法的菜单。获得用户选择的选项后，程序提示用户输入两个数字，然后执行用户刚才选择的操作。该程序只接受菜单提供的选项。程序使用float类型的变量储存用户输入的数字，如果用户输入失败，则允许再次输入。进行除法运算时，如果用户输入0作为第2个数（除数），程序应提示用户重新输入一个新值。该程序的一个运行示例如下：**
示例如下：
```
Enter the operation of your choice:
a. add s. subtract
m. multiply d. divide
q. quit
a
Enter first number: 22 .4
Enter second number: one
one is not an number.
Please enter a number, such as 2.5, -1.78E8, or 3: 1
22.4 + 1 = 23.4
Enter the operation of your choice:
a. add s. subtract
m. multiply d. divide
559
q. quit
d
Enter first number: 18.4
Enter second number: 0
Enter a number other than 0: 0.2
18.4 / 0.2 = 92
Enter the operation of your choice:
a. add s. subtract
m. multiply d. divide
q. quit
q
Bye.
```
```c
#include<stdio.h>
float get_number(void)
{
    float a;
    char c;
    
    while(scanf("%f",&a)!=1||a==0)
    {
        if(a==0)
        {
            printf("0 is not allowed,please input another number:");
            a=1;
            continue;
        }
        while((c=getchar())!='\n')
        putchar(c);
        printf(" is not allowed,please input another number:");
    }
    return a;
}
int main(void)
{
    char choice='a';
    float a;
    float b;
    do
    {
        printf("Enter the operation of your choice:\n");
        printf("a:add         s:subtract\nm:multiply       d:divide\nq:quit\n");
        choice=getchar();
        switch(choice)
        {
            case 'a':
            printf("Enter first number:");
            a=get_number();
            printf("Enter second number: ");
            b=get_number();
            printf("%.2f+%.2f=%.2f\n",a,b,a+b);
            break;
            case 's':
             printf("Enter first number:");
            a=get_number();
            printf("Enter second number: ");
            b=get_number();
            printf("%.2f-%.2f=%.2f",a,b,a-b);
            break;
            case 'm':
             printf("Enter first number:");
            a=get_number();
            printf("Enter second number: ");
            b=get_number();
            printf("%.2f*%.2f=%.2f",a,b,a*b);
            break;
            case 'd':
             printf("Enter first number:");
            a=get_number();
            printf("Enter second number: ");
            b=get_number();
            printf("%.2f/%.2f=%.2f",a,b,a/b);
            break;
            default:
            break;
        };
    }while(choice!='q');
    return 0;
}
```