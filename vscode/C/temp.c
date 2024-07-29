#include<stdio.h>

#define FEET (12 * 2.54)  
#define INCH 2.54
#define POUNDER 0.45359237

int main()
{
    int height,weight;
    scanf("%d %d",&height,&weight);
    int exchange_height_feet = height / FEET;
    double exchange_height_inch = (height - exchange_height_feet * FEET) / INCH;
    double exchange_weight_pounder = weight / POUNDER;
    printf("身高%d英尺%.2lf英寸,体重%.2lf磅",exchange_height_feet,exchange_height_inch,exchange_weight_pounder);
    return 0;
}