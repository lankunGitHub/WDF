## 第<font color=grey size=10>4</font>章
### 复习题

1. **再次运行程序1清单4.1,但是在要求输入人名时，请输入名和姓(根据英文书写习惯，姓和名中间有一个空格)，看看程序会发生什么情况。为什么?**
```
printf("Hi,What's your first name?\n");
scanf("%s",&name);
printf("%s,what's your weight in pound?\n",name);
scanf("%f",&weight)
```
原因：
```
scanf在读入时遇到第一个空格，换行符，制表符时，就会认为工作完成而不再读入，剩余输入被储存在缓冲区等待下一次读入
```
2. **假设下列示例都是完整程序中的一部分，它们打印的结果分别是什么？**
```
a.printf("He sold the painting for $%2.2f.\n", 2.345e2);
b.printf("%c%c%c\n", 'H', 105, '\41');
c.#define Q "His Hamlet was funny without being vulgar."
printf("%s\nhas %dcharacters.\n", Q, strlen(Q));
d.printf("Is %2.2e the same as %2.2f?\n", 1201.0, 1201.0);
```
结果如下：
```
a:He sold the painting for $234.50
b:Hi!
c:His Hamlet was funny without being vulgar.
  has 42 chracters.

d:Is 1.20e+03 the same as 1201.00?(+表示10的次方，-表示1/10的次方)

```
3. **在第2题的c中，要输出包含双引号的字符串Q，应如何修改？**
```
#define Q "\"His Hamlet was funny without being vulgar.\""
```
4. **找出下面程序中的错误。**
```c
define B booboo
define X 10
main(int)
{
int age;
char name;
printf("Please enter your first name.");
scanf("%s", name);
printf("All right, %c, what's your age?\n", name);
scanf("%f", age);
xp = age + X;
printf("That's a %s! You must be at least %d.\n", B, xp);
rerun 0;
}
```
改正如下：
```c
#include<stdio.h>
#defone B "booboo"
#define x 10
int main(void)
{
  int age,xp;
  cahr name[15];
  printf("Please enter your first name.");
  scanf("%s", &name);
  printf("All right, %s, what's your age?\n", name);
  scanf("%d",&age);
  xp = age + X;
  printf("That's a %s! You must be at least %d.\n", B, xp);
  return 0;
}
```
5. **假设一个程序的开头是这样：**
```c
#define BOOK "War and Peace"
int main(void)
{
float cost =12.99;
float percent = 80.0;
```
请构造一个使用BOOK、cost和percent的printf()语句，打印以下内容：
This copy of "War and Peace" sells for $12.99.
That is 80% of list.
```c
printf("This copy of %s sells for $%f",BOOK,cost);
printf("That is %.0f%% of list.",percent);
```
6. **打印下列各项内容要分别使用什么转换说明？**
```
a.一个字段宽度与位数相同的十进制整数    %d
b.一个形如8A、字段宽度为4的十六进制整数 %4x
c.一个形如232.346、字段宽度为10的浮点数  %10.3f
d.一个形如2.33e+002、字段宽度为12的浮点数   %12.2e
e.一个字段宽度为30、左对齐的字符串     %-30s
```
7. **打印下面各项内容要分别使用什么转换说明？**
```
a.字段宽度为15的unsigned long类型的整数  %15lu
b.一个形如0x8a、字段宽度为4的十六进制整数  %#4x
c.一个形如2.33E+02、字段宽度为12、左对齐的浮点数  %12.2e
d.一个形如+232.346、字段宽度为10的浮点数  %+10.3f
e.一个字段宽度为8的字符串的前8个字符   %8.8s
```
8. **打印下面各项内容要分别使用什么转换说明？**
```  
a.一个字段宽度为6、最少有4位数字的十进制整数  %6.4d
b.一个在参数列表中给定字段宽度的八进制整数   %*o
c.一个字段宽度为2的字符   %2c
d.一个形如+3.13、字段宽度等于数字中字符数的浮点数  %+.2f
e.一个字段宽度为7、左对齐字符串中的前5个字符   %-7.5s
```
9. **分别写出读取下列各输入行的scanf()语句，并声明语句中用到变量和数组。**
```
a.101
b.22.32 8.34E−09
c.linguini
d.catch 22
e.catch 22 （但是跳过catch）
```
```
scanf("%d",&a);
scanf("%f %e",&b1,&b2);
scanf("%s",c);
scanf("%s %d",&d1,&d2);
scanf("%*s %d",&e2);
```
10. **什么是空白？**
```
c语言中空白可以指空格，换行符，制表符
```
11. **下面的语句有什么问题？如何修正？**
```
printf("The double type is %z bytes..\n", sizeof(double));
```
```
printf("The double type is %zd bytes..\n", sizeof(double));
```
12. **假设要在程序中用圆括号代替花括号，以下方法是否可行？**
```
#define ( {
#define ) }
```
```
可以进行替换，但会发生语法错误，因为替换符号为c语言中的重要符号
```

### 编程练习
1. **编写一个程序，提示用户输入名和姓，然后以“名,姓”的格式打印出来。**
```c
#include<stdio.h>
int main(void)
{
  char name1[20];
  char name2[20]
  printf("请输入姓名：");
  scanf("%s",name1);
  scanf("%s",name2);
  printf("%s,%s",name1,name2);
}
```
2. **编写一个程序，提示用户输入名和姓，并执行一下操作：**
```
a.打印名和姓，包括双引号；
printf("\"%s\"",name);
b.在宽度为20的字段右端打印名和姓，包括双引号；
printf("\"%20s\"",name);
c.在宽度为20的字段左端打印名和姓，包括双引号；
printf("\"%-20s\"",name);
d.在比姓名宽度宽3的字段中打印名和姓。
printf("\"%3s\"",name);
```
3. **编写一个程序，读取一个浮点数，首先以小数点记数法打印，然后以
指数记数法打印。用下面的格式进行输出（系统不同，指数记数法显示的位数可能不同）：**
```
a.输入21.3或2.1e+001；
b.输入+21.290或2.129E+001；
```
```
scanf("%f",&a);
printf("%f %e");
```
4. **编写一个程序，提示用户输入身高（单位：英寸）和姓名，然后以下
面的格式显示用户刚输入的信息：**
```
Dabney, you are 6.208 feet tall
```
```c
#include<stdio.h>
#include<string.h>
int main(void)
{
  char name[40];
  float height;
  printf("请输入姓名：");
  gets(name);
  printf("请输入身高：");
  scanf("%f",&height);
  printf("%s, you are %.3f feet tall",name,height);
}
```
5. **编写一个程序，提示用户输入以兆位每秒（Mb/s）为单位的下载速度
和以兆字节（MB）为单位的文件大小。程序中应计算文件的下载时间。注
意，这里1字节等于8位。使用float类型，并用/作为除号。该程序要以下面的格式打印 3 个变量的值（下载速度、文件大小和下载时间），显示小数点后面两位数字：**
```
At 18.12 megabits per second, a file of 2.20 megabytes
downloads in 0.97 seconds.
```
```c
#include<stdio.h>
int main(void)
{
  float a,b,c;
  printf("请输入下载速度和文件大小：");
  c=b/a;
  printf("At %f megabits per second, a file of %f megabytes\ndownloads in %f seconds.",a,b,c);
}
```
