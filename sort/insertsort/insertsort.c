//思想：
//  给你一个无序的序列，从左边的第一个开始，维持一个有序的列表
//  比如 8，3 ，50， 100， 5，7，20，18，1，9
//  取第一个来说8算是有序，又取出下一个3，
//  前两个元素想要有序，
//  就需要维护这个有序表，
//  变成3，8，50，100, 
//  现在又来了一个5， 
//  他比100，50， 8 都要小，
//  应该插入到3的后面，
//  那么8，50，100就要往后面挪动
#include<stdio.h>

void insertsort(int a[], int n)
{
    for(int i = 1; i < n; i++) // 从第二个元素起，维持 （0 ---- i-1）这个序列的有序
    {
        //从 i - 1 开始寻找自己能够插入的位置
		if(a[i] < a[i -1])
		{
			int temp = a[i]; //临时把当前值存下来
			int j;
			for(j = i - 1; j >= 0 && a[j] > temp; j--)
			{
				a[j + 1] = a[j];
			}
			a[j + 1] = temp;
		}
    }
}

int main()
{
    int a[] = {8 ,3 ,50 ,100 ,5 ,7 ,20 ,18 ,1 ,9 };
    insertsort(a,10);

    for(int x = 0; x < 10; x++)
    {
        printf("%4d", a[x]);
    }
    printf("\n");

    return 0;
}
