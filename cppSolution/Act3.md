## 第<font color=grey size=10>3</font>章
### 复习题
1. **指出下面各种数据使用的合适类型(有些可以使用多种类型)**
```c
East Simpleton的入口(short)
DVD的价格(float)
本章出现次数最多的字母(char)
本章出现次数最多的字母的次数(int)
```
2. **在什么情况下要用long类型的变量代替int类型的变量**
```
long所能储存的数据范围更大，当我们储存的数据超过int的储存范围时，我们会用long代替int.
```
3. **使用哪些可移植的数据类型可以获得32位有符号整数？选择的理由是什么**
c语言可移植数据类型
```
C语言中的可移植数据类型是指具有确定大小和范围的数据类型，其大小和范围在不同的平台上是一致的。这些数据类型被定义在C标准库的头文件 <stdint.h> 中，其中包含了以下可移植数据类型：

    整数类型：
        int8_t：有符号8位整数
        uint8_t：无符号8位整数
        int16_t：有符号16位整数
        uint16_t：无符号16位整数
        int32_t：有符号32位整数
        uint32_t：无符号32位整数
        int64_t：有符号64位整数
        uint64_t：无符号64位整数

    最小宽度的整数类型：
        int_least8_t：至少8位的有符号整数
        uint_least8_t：至少8位的无符号整数
        int_least16_t：至少16位的有符号整数
        uint_least16_t：至少16位的无符号整数
        int_least32_t：至少32位的有符号整数
        uint_least32_t：至少32位的无符号整数
        int_least64_t：至少64位的有符号整数
        uint_least64_t：至少64位的无符号整数
        （"至少n位的有符号整数"指的是一个有符号整数类型，其大小至少为n位。这意味着它可以容纳至少n个二进制位。）

    最快宽度的整数类型：
        int_fast8_t：最快宽度的有符号整数
        uint_fast8_t：最快宽度的无符号整数
        int_fast16_t：最快宽度的有符号整数
        uint_fast16_t：最快宽度的无符号整数
        int_fast32_t：最快宽度的有符号整数
        uint_fast32_t：最快宽度的无符号整数
        int_fast64_t：最快宽度的有符号整数
        uint_fast64_t：最快宽度的无符号整数
（"最快宽度的有符号整数"指的是一个有符号整数类型，其大小是在当前平台上具有最高性能的整数类型。这意味着在当前平台上，这个整数类型的读写操作是最高效的。）
    指针相关类型：
        intptr_t：整数类型，足够容纳指针的值
        uintptr_t：无符号整数类型，足够容纳指针的值

这些可移植数据类型的定义保证了它们在不同平台上的大小和范围是一致的，使得编写可移植的C代码更加方便和可靠。
```
4. **指出下列常量的类型和含义**
```
'\b'   表示单个字符，\b表示退格字符
1066   表示一个整形常量
99.44  表示一个浮点数常量
0XAA   表示一个十六进制(对于八进制和十六进制整形数据，系统优先解释为无符号类型)
2.0e30 表示双精度浮点常量(编译器通常将浮点型常量解释为双精度类型)
```
5. **Dottie Cawm编写了一个程序，请找出其中的错误。**
```c
include<stdio.h>
main(
    float g;h;
    float tax,rate;
    g=e21;
    tax = rate*g;
)
```
修改如下
```c
#include<stdio.h>
int main(void)
{
    float g,h;
    float tax,rate;
    g=1.0e21;
    rate=0.08;
    tax=rate*g;
    h = g+tax;
    return 0;
}
```
6. **写出下列常量在声明中使用的数据类型和在printf()中对应的转换说明。**
```
12            int                    %d
0X3           unsigned int(十六进制)  %#x
‘C’           char                   %c
2.34e07       double                 %e(%e 是一个转换说明符，用于格式化输出浮点数类型中的科学计数法表示)
'\040'        char                   %c 
7.0           double                 %lf
6L            long                   %ld
6.0f          float                  %f
0x5.b6p12     float                  %a(%a 转换说明符用于将浮点数以十六进制格式输出，并且在输出中包含指数部分)
```
7. **写出下列常量在声明中使用的数据类型和在printf()中对应的转换说明(假设int为16位)**
```
012           unsigned int(八进制)    %#o
2.9e05L       long double            %Le
's'           char                   %c
100000        long                   %ld
'\n'          char                   %c
20.0f         float                  %f
0x44          unsigned int           %#x
-40           int                    %d
```
8. **假设程序的开头有以下声明。**
```c
int imate = 2;
long shot = 53456;
char grade = 'A';
float log = 2.71828;
```
把下面的printf()语句中的转换字符补充完整。
```
printf("The odds against the %d were %ld to 1.\n",imate,shot);
printf("A score of %f is not an %c grade.\n",log,grade);
```
9. **假设ch是char类型的变量，分别用转义序列，十进制，八进制和十六进制把回车字符赋给ch.**
```
char ch = '\r';
char ch = 13;
char ch = '\015';
char ch = '\xd';
```
10. **修正下面的程序**
```c
void main(int) /this program is perfect/
{
    cows,legs,integer;
    printf("How many cows legs did you count?\n");
    scanf("%c",legs);
    cows = legs/4;
    printf("That implies there are %f cows,\n",cows);
}
```
修改如下
```c
#include<stdio.h>
intt main(void)
{
    int cows,legs;
    printf("How many cows legs did you count?\n");
    scanf("%d",&legs);
    cows = legs/4;
    printf("That implies there are %d cows,\n",cows);
}
```
11. **指出下列转义序列的含义**
```
\n        表示换行
\\        表示转义\
\"        表示转义“
\t        表示水平制表符
```
<br>

### 编程题
1. **通过试验(即编写带有此类问题的程序)观察系统如何处理整数上溢，浮点数上溢和浮点数下溢的情况。**
```c
#include<stdio.h>
int main(void)
{
    int a=2147483647;
    float b=3.4e38;
    float c=0.111111111;
    printf("a=%d\n",a+1);
    printf("b=%f\n",b+1);
    printf("c=%f\n",c);
    return 0;
}
```
```
a=-2147483648
b=339999995214436424907732413799364296704.000000
c=0.111111
```
2. **编写一个程序，要求提示输入一个ASCII码值，然后打印输出的字符。**
```c
#include<stdio.h>
int main(void)
{
    int a;
    printf("请输入字符的ASCII码：");
    scanf("%d",&a);
    printf("%c\n",a);
    return 0;
}
```
3. **编写一个程序，发出一声警报，然后打印下列文本。**
```
Starled by the sudden sound, Sally shouted,
"By the Great Pumpkin, what was that!"
```
程序如下：
```c
#include<stdio.h>
int main(void)
{
    char a='\a';
    printf("%c",a);
    printf("Starled by the sudden sound, Sally shouted,\n\"By the Great Pumpkin, what was that!\"");
}
```
4. **编写一个程序，读取一个浮点数，先打印小数形式，后打印指数形式。然后，如果系统支持，再打印p计数法(即十六进制计数法)。按以下格式输出。**
```c
#include<stdio.h>
int main(void)
{
    float a;
    printf("请输入一个浮点数：");
    scanf("%f",&a);
    printf("%f\n",a);
    printf("%e\n",a);
    printf("%a\n",a);
    return 0;
}
```
```
1.250000
1.250000e+00
0x1.4p+0
```
5. **一年大约有3.156 x 10^7秒。编写一个程序，提示用户输入年龄，然后显示该年龄对应的秒数。**
```c
#include<stdio.h>
define year_second 3.156e7
int main(void)
{
    double second,year;
    printf("请输入您的年龄：");
    scanf("%lf",&year);
    second=year*year_second;
    printf("您的年龄对应的秒数为%e\n",second);
    return 0;
}
```
6. **一个水分子的质量约为3.0 x 10^-32克。1夸脱(1夸脱=0.000946立方米)水的质量大约是950克。编写一个程序，提示用户输入水的夸脱数，并显示水分子的数量。**
```c
#include<stdio.h>
#define WATER 3.0e-32
#deefine QURRT 950
in main(void)
{
    double nums,quartnums;
    printf("请输入夸脱的数量：");
    scanf("%lf",&quartnums);
    nums=quartnums*QUART/WATER;
    printf("水分子数为：%e",nums);
    return 0;
}
```
7. **1英寸相当于2.54厘米。编写一个程序，提示用户输入身高(单位是英寸)，然后以厘米为单位显示身高。**
```c
#include<stdio.h>
#define INCH_CM 2.54
in main(void)
{
    float height,inch;
    printf("请输入您的身高：");
    scanf("%f",&inch);
    height=inch*INCH_CM;
    printf("您的身高为：%.2f",height);
    return 0;
}
```
8. **在美国的测量体系中，1品脱(1品脱=0.4731765立方分米)等于2杯，1杯等于8盎司(1盎司=29.57353立方厘米)，1盎司大约等于2大汤勺，1大汤勺等于3茶勺。缩写一个程序，提示用户输入杯数，并且以品脱，盎司，汤勺，茶勺为单位显示等价容量。思考对于该程序，为何使用浮点型数据比整形数据更合适？**
```
在单位转化过程中，可能会出现浮点型数据，并且实际使用中，也可能有浮点型数据的输入
```
```c
#include<stdio.h>
#define PINT_CUP 2
#define CUP_OUNCE 8
#define OUNCE_SPOON 2
#define SPOON_TEA 3
int main(void)
{
    float numcup,pint,cup,ounce,spoon,tea;
    printf("请输入杯数：");
    scanf("%f",&numcup);
    pint=cup/PINT_CUP;
    ounce=cup*CUP_OUNCE;
    spoon=ounce*OUNCE_SPOON;
    tea=spoon*SPOON_TEA;
    printf("%f\n%f\n%f\n%f\n",pint,ounce,spoon,tea);
    return 0;
}
```