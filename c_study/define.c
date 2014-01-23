#include<stdio.h>

#define MAX 100000

int main() 
{

    for (int i = 0; i <= MAX; i++) 
    {
        printf("%d\t", i);
        if (i != 0 && i % 10 == 0)
        {
            printf("\n");
        }
    }
    return 0;
}
