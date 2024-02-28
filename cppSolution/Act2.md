## 第<font color=grey size=10>2</font>章
## c语言概述
<br>

### 复习题
1. **c语言的基本模块是什么**
```c
c语言的基本模块是函数。函数是可以重复使用的具有某一功能的语句块，可以提高开发效率。
```
2. **什么是语法错误？给出一个中文例子和c语言例子**
```c
中文例子：“作业写”（宾语应该放在动词后面）
c语言例子：“int a = 1”（缺少分号）
```
3. **什么是语义错误？给出一个中文例子和c语言例子。**
```c
中文例子：“我喜欢学习”（语法上是正确的，但表达的含义不正确，因为我不喜欢学习，所以所谓语义错误是指用正确的语法表示错误的内容）
c语言例子：“a == 1；”（我们本来想将a赋值为1,但实际确实表示a和1是否相等）
```
4. **Indiana Sloth编写了下面的程序，并征求你的意见，请你帮他评定。**
```c
include studio.h
int main{void}
(
    int s
    s :=56;
    printf(There are s weeks in a year.);
    return 0;
```
改错如下
```c
#include<stdio.h>
int main(void)
{
    int s;
    s = 56;
    printf("There are %d weeks in a year",s);
    return 0;
}
```
5. **假如下面的4个例子都是完整程序的一部分，它们分别输出什么结果？**
```c
a. printf("Baa Baa Black Sheep.");
   printf("Have you any wool!?\n");
b. printf("Begone!\nO Creature of lard!\n");
c. printf("What?\nNo/nfish?\n");
d. int num;
   num = 2;
   printf("%d + %d = %d",num,num,num+num);
```
输出如下：
```c
a. Baa Baa Black Sheep.
   Have you any wool!?
   (这是空格)
b. Begone!
   O Creature of lard!
   (这是空格)
c. What?
   No/nfish?
   (这是空格)
d. 2 + 2 = 4
```
6. **在main ,int ,function ,char ,= 中，哪些是c语言的关键字**
```c
main ,char ,int是关键字. =是运算符 ,function是自定义的标识符。
```
7. **如何以下面的格式输出变量words和lines的值(这里，3020和350代表两个变量的值)。**
```c
There were 3020 words and 350 lines.
```
```c
int words = 3020;
int lines = 350;
printf("There were %d words and %d lines.",words,lines);
```
8. **考虑下面的程序。**
```c
#include<stdio.h>
int main(void)
{
    int a,b;
    a = 5;
    b = 2;  /*第七行*/
    b = a;  /*第八行*/
    a = b;  /*第九行*/
    printf("%d   %d\n",b,a);
    return 0;
}
```
请问，在执行完第7,8,9行后，程序的状态分别是什么。
```c
第七行：b被赋值为2；
第八行：b被赋值为a,为5；
第九行：a被赋值为b,为5；
```
9. **考虑下面的程序。**
```c
#include<stdio.h>
int main(void)
{
    int x,y;
    x = 10;
    y = 5;      /*第七行*/
    y = x + y;  /*第八行*/
    x = x*y;    /*第九行*/
    printf("%d   %d\n",x,y);
    return 0;
}
```
请问，在执行完第7,8,9行后，程序的状态分别是什么。
```c
第七行：y被赋值为5；
第八行：y等于y(5)加上x(10)为15；
第九行：x等于x(10)乘y(15)为150；
```
### 编程练习
1. **编写一个程序，调用一次printf()函数，ba你的名和姓打印在一行。再调用一次printf()函数，把你的名和姓分别打印到两行。然后，再调用两次printf()函数，把你的名和姓打印在一行。**
示例输出如下：
```c
Gustav Mahler  /*第一次打印内容*/
Gustav         /*第二次打印内容*/
Mahler         
Gustav Mahler  /*第三次打印内容*/
```

```c
#include<stdio.h>
int main(void)
{
    printf("Gustav Mahler");
    printf("Gustav\nMahler");
    printf("Gustav ");
    printf("Mahler");
    return 0;
}
```
2. **编写一个程序，打印你的姓名和地址。**
```c
#include<stdio.h>
int main(void)
{
    printf("名字\n地址");
    return 0;
}
```
3. **编写一个程序，把你的年龄换成天数，并显示年龄和天数。这里不用考虑闰年的问题。**
```c
#include<stdio.h>
#define year 365
int main(void)
{
    int age,day;
    scanf("%d",&age);
    day = age*year;
    printf("age=%d day=%d",age,day);
    return 0;
}
```
4. **编写一个程序，生成以下输出**
```c
For he's a jolly good fellow!
For he's a jolly good fellow!
For he's a jolly good fellow!
Which nobody can deny!
```
除main()函数外，该程序还要调用两个自定义函数：一个名为jolly()，用来打印前3条消息，调用一次打印一条；另一个函数名为deny()，打印最后一条消息。
```c
#include<stdio.h>
void jolly(void)
{
    printf("For he's a jolly good fellow!");
}
void deny(void)
{
    printf("Which nobody can deny!");
}

int main(void)
{
    jolly();
    jolly();
    jolly();
    deny();
    return 0;
}
```
5. **编写一个程序，生成以下输出**
```c
Brazil, Russia, India, China
India, China,
Brazil, Russia
```
除main()函数外，该程序还要调用两个自定义函数：一个名为br()，调用一次打印一次"Brazil, Russia"；另一个函数名为ic()，调用一次打印一次"India, China".其他功能在mian()函数实现。
```c
#include<stdio.h>
void br(void)
{
    printf("Brazil, Russia");
}
void ic(void)
{
    printf("India, China");
}

int main(void)
{
    printf("%s, %s\n%s,\n%s",br(),ic(),ic(),br());
    return 0;
}
```
6. **编写一个程序，创建一个整形变量toes,并将toes设置为10,程序中还要计算toes的两倍和toes的平方。该程序打印3个值，并分别描述以区别。**
```c
#include<stdio.h>
int main(void)
{
    int toes = 10;
    printf("toes = %d,toes的两倍 = %d,toes的平方 = %d"，toes,2*toes,toes*toes);
    return 0;
}
```
7. **许多研究表明，微笑多多益善，编写一个程序，生成以下格式的输出。**
```c
Smile!Smile!Smile!
Smile!Smile!
Smile!
```
该程序要定义一个函数，调用该函数一次打印一次“Smile!”，根据程序的需要使用该函数。
```c
#include<stdio.h>
void smile(void)
{
    printf("Smile!");
}

int main(void)
{
    smile();smile();smile();
    printf("\n");
    smile();smile();
    printf("\n");
    smile();
    return 0;
}
```
8. **在c语言中，一个函数可以调用另一个函数。编写一个程序，用于调用一个名为one_three()函数，该函数在一行打印“One”，再调用另一个函数two()，然后在另一行打印单词“three”。two()函数在一行显示单词“two”。main()函数在调用one_three()函数前要打印短语“Staring now：”，并在调用完毕后显示短语“Done！”。应此，该程序的输出如下所示。**
```c
Staring now;
one
two
three
Done!
```
```c
#include<stdio.h>
void two(void)
{
    printf("two\n");
}
void one_three(void)
{
    printf("one\n");
    two();
    printf("three");
}

int main(void)
{
    printf("Staring now：");
    one_three();
    printf("Done!");
}
```