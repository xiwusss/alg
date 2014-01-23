//思想: 相邻两数比较,小数放前面 
//算法平均时间复杂度: O(n^2)
//优点 ： 稳定
//确定 ： 太慢, 比较次数太多，每一趟相邻元素进行比较(o(n^2))
#include<stdio.h>

void swap(int arr[], int index_x, int index_y);

//未优化
void bubblesort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++)//要进行的比较的趟数，最后一趟没有必要了。 
    { 
        for (int j = 0; j < n - i - 1 ; j++) //挨个挨个的比较 n - i 的意思是沉到最下面的已经是最大的了，没有必要再比较了。
        { 
            if (arr[j] > arr[j + 1]) //前一个比后一个大，让大的往后面沉
            { 
                swap(arr, j, j + 1);
            }
        }
    }
}

//优化过的
void opt_bubblesort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++) //要进行的比较的趟数，最后一趟没有必要了。
    { 
        int isSort = 1; //用一个标志，表示这个序列是否已经有序，如果有序，没有必要在进行比较了, 没有本质的区别，最坏情况下也是o(n^2)
        for (int j = 0; j < n - i - 1 ; j++) //挨个挨个的比较 n - i 的意思是沉到最下面的已经是最大的了，没有必要再比较了。
        {
            if (arr[j] > arr[j + 1]) //前一个比后一个大，让大的往后面沉
            { 
                swap(arr, j, j + 1);
                isSort = 0;
            }
        }

        if (isSort) 
        {
            break;
        }

        isSort = 1;
    }
}

int main()
{
    int a[10] = {1,23,4,54,7,67,879,24,325,565};
    bubblesort(a, 10);
    printf("排序结果为：");
    for(int i = 0; i < 10; i++){
        printf("%5d", a[i]);
    }
    printf("\n");

    printf("------------------------------------------------\n");

    int b[10] = {10,23,4,54,7,67,879,24,325,565};
    opt_bubblesort(b, 10);
    printf("排序结果为：");
    for(int i = 0; i < 10; i++){
        printf("%5d", b[i]);
    }
    printf("\n");


    return 0;
}
