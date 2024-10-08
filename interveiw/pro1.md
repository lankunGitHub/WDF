# 题目：算的什么玩意这是(#`Д´)ﾉ

| 出题人 | 兰坤              |
|--------|----------------------|
| 知识点1   |  类型转换         |
|    知识点2    |  数据类型的储存   |

### 问题一
**为什么y值与x值不相等，如何修改可以使x与y值相等？**  
答：3和2为整数类型，进行整数除法，会发生向下取整生成一个整数类型（可以进一步询问sizeof(3 / 2)的值为多少及原因），随后隐式转换为double类型。若想相等，可以将其中一项改为浮点数类型。

### 问题二
**关于C语言的类型转换你了解多少？**  
答：C语言的类型转换主要有两种：隐式转换和显式转换，隐式转换由编译器自动进行。需要注意在类型转换中，（重要点）可能会出现精度丢失的问题。

### 问题三
**为什么c值与x值不相等？**  
答：在计算机中储存浮点数存在精度误差，某些十进制小数，如0.1，无法在二进制中精准表示。

### 问题四
**你了解计算机如何储存C语言各种数据类型吗？**  
答：首先需要了解位和字节的概念<br>对于整数，首先需要明确是以二进制补码的形式储存（询问一下原码，反码，补码的知识点），其中，首位为符号位（条件允许可以随机举一个数纸上回答[最好是负数，这样可以判断是否转成了补码])<br>
对于浮点数，以IEEE 754为准(-1)^S * M * 2^E，首先有一位符号位（S），然后是指数位（E），指数位需要减去偏移量（减去偏移量的原因是为了表示负的指数，可以询问一下为什么要减去偏移量） 接下来是小数位（M），M值在1至2之间，可以不用过多考究小数位如何求出，能说出更好，但是需要指出小数位无法精确表示是导致浮点数储存存在误差的原因<br>
对于字符类型，以ASCII码形式储存


### 评判标准
- **A**：准确说明程序运行结果，清晰了解各数据类型储存形式。
- **B**：正确说明程序结果，大致了解数据类型储存形式。
- **C**：部分正确说明程序结果，了解数据类型储存形式。
- **D**：无法正确说明程序结果，基本不了解数据类型储存形式。

```c
#include <stdio.h>

int main () {
    double x = 1.5000;
    double y = 3 / 2;

    if(x == y) {
        printf("x = y\nx =%lf  y = %lf\n\n", x, y);
    }
    else {
        printf("x != y\nx=%lf  y=%lf\n\n", x, y);
    }
    
    double c = 0;
    for(int i = 0; i < 15; i++) {
        c += 0.1f;
    }
    
    if(x == c) {
        printf("x = c\nx =%lf  c = %lf\n\n", x, c);
    }
    else {
        printf("x != c\nx=%lf  c=%lf\n\n", x, c);
    }
}
```
