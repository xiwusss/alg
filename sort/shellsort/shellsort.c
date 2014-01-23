//思想：
//    又名： 缩小增量排序,本质就是插入排序，
//    举个例子8, 3, 50, 100, 5, 7, 20, 18, 1, 9;
//    先把这堆无序的数字分为几堆，没有对都进行插入排序
//    分堆是一个很难的地方, incremented = 10
//    一般我们incremented = incremented / 3 + 1, 就是间隔为4，
//    分堆一般就为 4， 2, 1

#include<stdio.h>

void shellinsert(int a[], int n, int dk)
{
    for(int i = dk; i < n; i++) // 从第二个元素起，维持 （0 ---- i-1）这个序列的有序
    {
        //从 i - 1 开始寻找自己能够插入的位置
		if(a[i] < a[i - dk])
		{
			int temp = a[i]; //临时把当前值存下来
			int j;
			for(j = i - dk; j >= 0 && a[j] > temp; j -= dk)
			{
				a[j + dk] = a[j];
			}
			a[j + dk] = temp;
		}
    }
}

void shellsort(int a[], int n)
{
    int incremented = n;
    while(incremented > 1)
    {
        incremented = incremented / 3 + 1;
        shellinsert(a,n,incremented);
    }
}

int main()
{
    int a[] = {8 ,3 ,50 ,100 ,5 ,7 ,20 ,18 ,1 ,9 };
    shellsort(a,10);

    for(int x = 0; x < 10; x++)
    {
        printf("%4d", a[x]);
    }
    printf("\n");
	
    return 0;
}

