//思想：
//每一趟从待排序的数据元素中选出最小（或最大）的一个元素，
//顺序放在已排好序的数列的最后，直到全部待排序的数据元素排完。
//优点：简单
//缺点：比较次数太多。
#include<stdio.h>

void swap(int a[], int index_x, int index_y); 

// 没有优化的，比较次数和交换次数非常的频繁
void selectsort(int a[], int n)
{
    for(int i = 0; i < n; i++)//每一趟
    {
        for(int j = i + 1; j < n; j++)// 让a[i] 和a[j]中的所有元素比较，找到最大的或者最小的,就是俗称的打擂台
        {
            if(a[i] > a[j])
            {
                swap(a, i, j);
            }
        }
    }
}

// 优化过的，比较次数和交换次数非常的频繁
void optselectsort(int a[], int n)
{
    for(int i = 0; i < n; i++)//每一趟
    {
        int index = i;
        for(int j = i + 1; j < n; j++)// 让a[i] 和a[j]中的所有元素比较，找到最大的或者最小的,就是俗称的打擂台
        {
            if(a[index] > a[j])// 只是记录剩下元素中最小值的位置即可，不要出现那么多的交换
            {
               index = j; 
            }
        }

        if(index != i)// 交换
        {
           swap(a, i, index); 
        }
    }
}

void swap(int a[], int index_x, int index_y) 
{
    int temp;
    temp = a[index_x];
    a[index_x] = a[index_y];
    a[index_y] = temp;
}

int main()
{
    int a[10] = {50,21,12,65,6,9,10,2,19,48};
    //selectsort(a, 10);
    optselectsort(a, 10);

    for(int i = 0; i < 10; i++)
    {
        printf("%4d", a[i]);
    }
    printf("\n");

    return 0;
}
