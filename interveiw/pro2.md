# 递递归归无穷尽也

| 出题人 | 兰坤              |
|--------|----------------------|
| 知识点1   |  递归的使用         |

## 题目
汉诺塔（Hanoi Tower）是一个经典的问题，源于印度一个古老传说。大梵天创造世界时做了三根金刚石柱子，初始时64片黄金圆盘从下往上按照大小顺序摞在A柱上。任务是将这些圆盘按大小顺序移动到C柱上，移动时只能一次移动一个圆盘，且小圆盘不能放在大圆盘上。

## 问题一
**你能简述程序的执行过程吗？**

**答：原理：**
1. 将n-1个圆盘从A杆经C杆移动到B杆。
2. 将A杆上的第n个圆盘移动到C杆。
3. 将n-1个圆盘从B杆经A杆移动到C杆。

## 问题二
**你了解递归吗，它有什么特点？**

**答：** 递归是一种方法，指函数调用自身以解决更小规模的问题。特点包括：
- 自我调用：递归函数直接或间接调用自身。
- 基准条件：每个递归函数需要终止条件以避免无限循环。
- 分治思想：将问题分解为简单子问题逐步求解。
- 代码简洁：使得解决方案更简洁，适合处理树形数据。
- 内存使用：递归消耗栈空间，过深的递归可能导致栈溢出。

## 评判标准
- **A**：准确清晰描述整个递归过程，特别是分治思想的体现，清楚了解递归特点。
- **B**：正确描述整个递归过程，了解递归特点。
- **C**：较为正确描述递归过程，了解递归特点。
- **D**：无法正确描述递归过程，但了解递归特点。

## 代码
```c
#include <stdio.h>

void hanoi(int n, char source, char target, char auxiliary) {
    if (n == 1) {
        printf("Move disk 1 from %c to %c\n", source, target);
        return;
    }
    hanoi(n - 1, source, auxiliary, target);
    printf("Move disk %d from %c to %c\n", n, source, target);
    hanoi(n - 1, auxiliary, target, source);
}

int main() {
    int n;
    printf("Enter the number of disks: ");
    scanf("%d", &n);
    if (n < 1) {
        printf("Please enter a positive integer.\n");
        return 1; 
    }
    hanoi(n, 'A', 'C', 'B');
    return 0;
}