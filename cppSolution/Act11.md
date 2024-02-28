### 编程练习
1. **设计并测试一个函数，从输入中获取下n个字符（包括空白、制表符、换行符），把结果储存在一个数组里，它的地址被传递作为一个参数。**
```c
#include<stdiio.h>
void get(char *ch,int n)
{
    for(int i=0;i<n;i++)
    {
        *(ch+i)=getchar();
    }
}
int main(void)
{
    char ch[10];
    get(ch,10);
    for(int i=0;i<10;i++)
    {
        printf("%c",ch[i]);
    }
}
```
2. **修改并编程练习1的函数，在n个字符后停止，或在读到第1个空白、制表符或换行符时停止，哪个先遇到哪个停止。不能只使用scanf()。**
```c
#inlcude<stdio.h>
void get(char *ch,int n)
{
    for(int i=0;i<n;i++)
    {
        *(ch+i)=getchar();
        if(*(ch+i)=='\n'||*(ch+i)=='\t'||*(ch+i)==' ')  break;
    }
}
int main(void)
{
    char ch[10];
    get(ch,10);
    for(int i=0;i<10;i++)
    {
        printf("%c",ch[i]);
    }
}
```
3. **设计并测试一个函数，从一行输入中把一个单词读入一个数组中，并丢弃输入行中的其余字符。该函数应该跳过第1个非空白字符前面的所有空白。将一个单词定义为没有空白、制表符或换行符的字符序列。**
```c
#include<stdio.h>
char* getword(char *a)
{
    char b[15];
    fgets(b,15,stdin);
    int count=0,i;
    while(b[count]==' '||b[count]=='\t'||b[count]=='\n')
    count++;
    while(b[count]!=' '&&b[count]!='\t'&&b[count]!='\n')
    {
        a[i]=b[count];
        i++;
        count++;
    }
    a[i]='\0';
    return a;
}
int main(void)
{
    char a[15];
    getword(a);
    printf("%s",a);
}
```
4. **设计并测试一个函数，它类似编程练习3的描述，只不过它接受第2个参数指明可读取的最大字符数。**
```c
char* getword(char *a,int n)
{
    char b[15];
    fgets(b,15,stdin);
    int count=0,i;
    while(b[count]==' '||b[count]=='\t'||b[count]=='\n')
    count++;
    while(b[count]!=' '&&b[count]!='\t'&&b[count]!='\n'&&i<n)
    {
        a[i]=b[count];
        i++;
        count++;
    }
    a[i]='\0';
    return a;
}
int main(void)
{
    int n;
    char a[15];
    scanf("%d",&n);
    getword(a,n);
    printf("%s",a);
}
```
5. **设计并测试一个函数，搜索第1个函数形参指定的字符串，在其中查找第2个函数形参指定的字符首次出现的位置。如果成功，该函数返指向该字符的指针，如果在字符串中未找到指定字符，则返回空指针（该函数的功能与 strchr()函数相同）。在一个完整的程序中测试该函数，使用一个循环给函数提供输入值。**
```c
#include<stdio.h>
char *find(char *ret,char a)
{
    while(*ret!='\0')
    {
        if(*ret==a)  return ret;
        else   ret++;
    }
    ret=NULL;
    return ret;
}
```
6. **编写一个名为is_within()的函数，接受一个字符和一个指向字符串的指针作为两个函数形参。如果指定字符在字符串中，该函数返回一个非零值（即为真）。否则，返回0（即为假）。在一个完整的程序中测试该函数，使用一个循环给函数提供输入值。**
```c
#include<stdio.h>
char find(char *ret,char a)
{
    while(*ret!='\0')
    {
        if(*ret==a)  return 1;
        else   ret++;
    }
    return 0;
}
```
7. **strncpy(s1, s2, n)函数把s2中的n个字符拷贝至s1中，截断s2，或者有必要的话在末尾添加空字符。如果s2的长度是n或多于n，目标字符串不能以空字符结尾。该函数返回s1。自己编写一个这样的函数，名为mystrncpy()。在一个完整的程序中测试该函数，使用一个循环给函数提供输入值。**
```c
char *mystrncpy(char *s1,char *s2,int n)
{
    int a=strlen(s1);
    for(int i=0;i<n;i++)
    {
      s1[a+i]=s2[i];
      if(s2[i]=='\0')  break;
    }
    s1[a+n]='\0';
    return s1;
}
```
8. **编写一个名为string_in()的函数，接受两个指向字符串的指针作为参数。如果第2个字符串中包含第1个字符串，该函数将返回第1个字符串开始的地址。例如，string_in("hats", "at")将返回hats中a的地址。否则，该函数返回空指针。在一个完整的程序中测试该函数，使用一个循环给函数提供输入值。**
```c
char *string_in(char *s1,char *s2)
{
    int s1_len=strlen(s1);
    int s2_len=strlen(s2);
    printf("%d   %d\n",s1_len,s2_len);
    int count=0;
    for(int i=0;i<s1_len;i++)
    {
        if(*(s1+i)==*(s2+count))
        {
            printf("%c h\n",*(s1+i));
            count++;
            if(count==s2_len)
            {
                return s1+i+1-count;
            }
        }
        else  count=0;
    }
    return NULL;
}
```
9. **编写一个函数，把字符串中的内容用其反序字符串代替。在一个完整的程序中测试该函数，使用一个循环给函数提供输入值。**
```c
void excahnge(char *a)
{
    char temp;
    int len=strlen(a);
    for(int i=0;i<len/2;i++)
    {
        temp=a[i];
        a[i]=a[len-1-i];
        a[len-1-i]=temp;
    }
}
```
10. **编写一个函数接受一个字符串作为参数，并删除字符串中的空格。在一个程序中测试该函数，使用循环读取输入行，直到用户输入一行空行。该程序应该应用该函数只每个输入的字符串，并显示处理后的字符串。**
```c
char *deleteBlock(char *a)
{
     char *s=a;
     while(*a!='\0')
     {
        if(*a!=' ')  *s++=*a++;
        else    a++;
     }
     *s++='\0';
     return a;
}
```
11. **编写一个函数，读入10个字符串或者读到EOF时停止。该程序为用户提供一个有5个选项的菜单：打印源字符串列表、以ASCII中的顺序打印字符串、按长度递增顺序打印字符串、按字符串中第1个单词的长度打印字符串、退出。菜单可以循环显示，除非用户选择退出选项。当然，该程序要能真正完成菜单中各选项的功能。**
```c
#include<stdio.h>
#define SIZE 20
void tenString(char a[10][SIZE])
{
    int i=0;
    do
    {
        fgets(a[i],SIZE,stdin);
        i++;
    } while (a[i]!=EOF&&i<10);
}
void ascPrint(char a[10][SIZE])
{
    char temp[SIZE];
    for(int i=0;i<9;i++)
    {
        for(int k=0;k<9-i;k++)
        {
            if(*a[k]>*a[k+1])
            {
                strcpy(temp,a[k]);
                strcpy(a[k],a[k+1]);
                strcpy(a[k+1],temp);
            }
        }
    }
    for(int i=0;i<10;i++)
    {
        printf("%s",a[i]);
    }
}
void lenPrint(char a[10][SIZE])
{
    char temp[SIZE];
    for(int i=0;i<9;i++)
    {
        for(int k=0;k<9-i;k++)
        {
            if(strlen(a[k])>strlen(a[k+1]))
            {
                strcpy(temp,a[k]);
                strcpy(a[k],a[k+1]);
                strcpy(a[k+1],temp);
            }
        }
    }
    for(int i=0;i<10;i++)
    {
        printf("%s",a[i]);
    }
}
void wordPrint(char a[10][SIZE])
{
    short len[10][1]={0};
    for(int i=0;i<10;i++)
    {
        int k=0;
        while(a[i][k]!=' '&&a[i][k]!='\n'&&a[i][k]!='\t')
        {
            k++;
            len[i][0]++;
        }
    }
    char temp[SIZE];
    for(int i=0;i<9;i++)
    {
        for(int k=0;k<9-i;k++)
        {
            if(len[k][0]>len[k+1][0])
            {
                strcpy(temp,a[k]);
                strcpy(a[k],a[k+1]);
                strcpy(a[k+1],temp);
            }
        }
    }
    for(int i=0;i<10;i++)
    {
        printf("%s",a[i]);
    }
    
}
int main(void)
{
    char b='1';
    char a[10][SIZE];
    while(a!='q')
    {
        printf("enter 10 string");
        tenString(a);
        printf("1:printf by asc    2:printf by lenth\n");
        printf("3:printf by wordlenth   q: quit\n");
        scanf("%c",&b);
        switch(b)
        {
            case '1':
                ascPrint(b);
                break;
            case '2':
                lenPrint(b);
                break;
            case '3':
                wordPrint(b);
                break;
            case 'q':
                break;
        };
    }
    return 0;
}
```
