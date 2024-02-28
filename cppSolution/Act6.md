### 编程练习
15. **编写一个程序，读取一行输入，然后把输入的内容倒序打印出来。可以把输入储存在char类型的数组中，假设每行字符不超过255。回忆一下，根据%c转换说明scanf()函数一次只能从输入中读取一个字符，而且在用户按下Enter键时scanf()函数会生成一个换行字符（\n）。**
```c
#include<stdio.h>
#include<string.h>
int main(void)
{
    char arr[256];
    int i=0;
    do
    {
        scanf("%c",&arr[i]);
        
        
    }while(arr[i]!='\n'&&++i);
    for(int k=i-1;k>=0;k--)
    {
        printf("%c",arr[k]);
    }
    return 0;
}
```
16. **Daphne以10%的单利息投资了100美元（也就是说，每年投资获利相当于原始投资的10%）。Deirdre以 5%的复合利息投资了 100 美元（也就是说，利息是当前余额的 5%，包含之前的利息）。编写一个程序，计算需要多少年Deirdre的投资额才会超过Daphne，并显示那时两人的投资额**
```c
#include<stdio.h>
int main(void)
{
    double da=100,de=100;
    int year=0;
    while(da>=de)
    {
        da+=100*0.1;
        de=de*1.05;
        year++;
    }
    printf("%d",year);
}
```
17. **Chuckie Lucky赢得了100万美元（税后），他把奖金存入年利率8%的账户。在每年的最后一天， Chuckie取出10万美元。编写一个程序，计算多少年后Chuckie会取完账户的钱？**
```c
#include<stdio.h>
int main(void)
{
    int year=0;
    double money=1000000;
    while(money>0)
    {
        money=(money-100000)*1.08;
        year++;
    }
    printf("%d",year);
}
```
18. **Rabnud博士加入了一个社交圈。起初他有5个朋友。他注意到他的朋友数量以下面的方式增长。第1周少了1个朋友，剩下的朋友数量翻倍；第2周少了2个朋友，剩下的朋友数量翻倍。一般而言，第N周少了N个朋友，剩下的朋友数量翻倍。编写一个程序，计算并显示Rabnud博士每周的朋友数量。该程序一直运行，直到超过邓巴数（Dunbar’s number）。邓巴数是粗略估算一个人在社交圈中有稳定关系的成员的最大值，该值大约是150。**
```c
#include<stdio.h>
int main(void)
{
    nt friend=5,day=1;
    while(friend<150)
    {
        friend=(friend-1)*2;
        day++;
        printf("第%d天朋友数：%d\n",day,friend);

    }
}
```