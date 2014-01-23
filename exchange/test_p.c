#include<stdio.h>

void test_p(int* p1)
{
    int x = 10;
    *p1 = x;
}

int main()
{
    int a = 5;
    int* p1 = &a;
    test_p(p1);
    printf("%5d\n", *p1);
}
