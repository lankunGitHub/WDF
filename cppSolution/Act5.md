### 编程练习
4. **编写一个程序，提示用户输入一个身高（单位：厘米），并分别以厘米和英寸为单位显示该值，允许有小数部分。程序应该能让用户重复输入身高，直到用户输入一个非正值。其输出示例如下：**
```
Enter a height in centimeters: 182
182.0 cm = 5 feet, 11.7 inches
Enter a height in centimeters (<=0 to quit): 168.7
168.0 cm = 5 feet, 6.4 inches
Enter a height in centimeters (<=0 to quit): 0
bye
```
```c
#include<stdio.h>
#define CM_INCH 0.39370079
#define CM_FEET 0.0328084
int main(void)
{
    DOUBLE height;
    printf("Enter a height in centimeters: ");
    scanf("%f",&height);
    printf("%f cm = %.0f feet, %.1f inches",height,height*CM_FEET,height*CM_INCH);
    while(height>0)
    {
        printf("nter a height in centimeters (<=0 to quit):");
        scanf("%f",&height);
    }
    printf("bye");
}
```
5. **编写一个程序，提示用户输入一个double类型的数，并打印该数的立方值。自己设计一个函数计算并打印立方值。main()函数要把用户输入的值传递给该函数。**
```c
#include<stdio.h>
double trble(double a)
{
    return a*a*a;
}
int main(void)
{
    double a;
    printf("请输入数值：");
    scanf("%lf",&a);
    printf("%lf",trble(a));
    return 0;
}
```
8. **编写一个程序，显示求模运算的结果。把用户输入的第1个整数作为求模运算符的第2个运算对象，该数在运算过程中保持不变。用户后面输入的数是第1个运算对象。当用户输入一个非正值时，程序结束。其输出示例如下：**
```
This program computes moduli.
Enter an integer to serve as the second operand: 256
Now enter the first operand: 438
438 % 256 is 182
Enter next number for first operand (<= 0 to quit): 1234567
1234567 % 256 is 135
Enter next number for first operand (<= 0 to quit): 0
Done
```
```c
#include<stdio.h>
int main(void)
{
    
    int a,b;
    printf("This program computes moduli.\n");
    printf("Enter an integer to serve as the second operand: ");
    scanf("%d",&a);
    printf("Now enter the first operand: ");
    scanf("%d",&b);
    printf("%d %% %d is %d \n",b,a,a%b);
    while(b>0)
    {
        printf("Enter next number for first operand (<= 0 to quit): ");
        scanf("%d",&b);
        printf("%d %% %d is %d ",b,a,a%b);
    }
    printf("Done!");
}
```
9. **编写一个程序，要求用户输入一个华氏温度。程序应读取double类型的值作为温度值，并把该值作为参数传递给一个用户自定义的函数Temperatures()。该函数计算摄氏温度和开氏温度，并以小数点后面两位数字的精度显示3种温度。要使用不同的温标来表示这3个温度值。下面是华氏温度转摄氏温度的公式：**
**摄氏温度 = 5.0 / 9.0 * (华氏温度 - 32.0)**
**开氏温标常用于科学研究，0表示绝对零，代表最低的温度。下面是摄氏温度转开氏温度的公式：**
**开氏温度 = 摄氏温度 + 273.16**
**Temperatures()函数中用const创建温度转换中使用的变量。在main()函数中使用一个循环让用户重复输入温度，当用户输入 q 或其他非数字时，循环结束。scanf()函数返回读取数据的数量，所以如果读取数字则返回1，如果读取q则不返回1。可以使用==运算符将scanf()的返回值和1作比较，测试两值是否相等。**
```c
#include<stdio.h>
   double Temperatures(double a)
{
    const double b=5.0 / 9.0 * (a - 32.0);
    printf("摄氏温度为%lf",b);
    const double c=b + 273.16;
    printf("开氏温度为%lf",c);
    return 1;
}
int main(void)
{
    double a;
    printf("请输入温度：");
    scanf("%lf",&a);
    Temperatures(a);
    while(scanf("%lf",&a)==1)
    {
        printf("请输入温度：");
    scanf("%lf",&a);
    Temperatures(a);
    }
    return 0;
}
```