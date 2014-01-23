#include<stdio.h>

void swap01(int *a ,int *b)
{
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

void swap02(int *a ,int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}


int main()
{
    int a = -7;
    int b = -5;
    swap02(&a, &b);
    printf("%5d\t%5d\n", a, b);
    //swap01(&a, &b);
    //kprintf("%5d\t%5d\n", a, b);
    return 0;
}
