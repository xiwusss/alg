//思想：
//    条件：两个序列都是有序，a[], b[],取出a的第一个和b的第一个比较
//    放入新的序列,这样一直做下去
#include<stdio.h>

void merge(int a[], int b[], int c[], int m, int n) 
{
    int k = 0;
    int i = 0;
    int j = 0;
    while(i < m && j < n)
    {
        if(a[i] < b[j])
        {
            c[k++] = a[i++];
        }
        else
        {
            c[k++] = b[j++];
        }
    }



    if (i < m) 
    {
        for(int p = i;p < m; p++)
        {
            c[k++] = a[p];
        }
    }

    if (j < n) 
    {
        for(int p = j;p < n; p++)
        {
            c[k++] = b[p];
        }
    }
}

int main()
{
    int a[] = {3,4,5,60,70,80,100};
    int b[] = {6,7,8,30,40,50};

    int c[] = {0,0,0,0,0,0,0,0,0,0,0,0};
    merge(a,b,c,7,6);

    for(int i = 0; i < 13; i++)
    {
        printf("%4d", c[i]);
    }
    printf("\n");


}
