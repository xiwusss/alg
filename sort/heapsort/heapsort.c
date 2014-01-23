//思想：
//  选择排序的加强版
//  heap 是一颗完全二叉树，可以把数组填满，所以就用数组表示
//  给你一个无须的数组序列，首先是建堆的过程。
//  找到最后一个不是叶子的节点 就是n/2
//  开始建立堆
//  一般都是从1开始，因为，如果第一个元素是 0， 2 * i 和 2 * i + 1 不太好处理
#include<stdio.h>

//{1,38,65,97,76,3,7,5} 
int LT(int a, int b) 
{
    if (a < b ) return 1;
    return 0;
}

void heapadjust(int a[], int start, int end)
{
    int rc = a[start];
    for(int j = 2 * start; j <= end; j *= 2) //沿key较大的孩子节点向下筛选
    {
        if(j < end && LT(a[j], a[j+1])) j++; //判断两个儿子左右两边 谁打谁小 如果是右边大，j++ 
        if(!LT(rc,a[j])) break; //让 胜出的那个儿子和父亲比较谁打谁小，如果是父亲大，那么没有必要再比较下去了。break，终止，因为这种情况下，已经是一个大顶堆了。
        a[start] = a[j];//如果父亲都比左右其中的某一个小了。那么两个就交换位置。
        a[j] = rc;
        start = j;
    }
    //a[start] = rc;
}

void heapsort(int a[], int n)
{
    for(int i = n/2; i >= 1; i--) //从最后一个不是叶子节点的地方调整
    {
        heapadjust(a, i, n);
    }

/*
    for(int i = 1; i <= n; i++)
    {
        printf("%4d", a[i]);
    }
    printf("\n");
*/

    for(int i = n ; i >= 1; i--)
    {
        //printf("%4d\n", a[1]);
        a[1] = a[i];
        heapadjust(a,1, i - 1);

   /* 
        for(int x = 1; x < i; x++)
        {
            printf("%4d", a[x]);
        }
        printf("\n");
    */

    }
}

int main()
{
    int a[16] = {0,1,38,222,555,6789,43,21,67,98,65,97,76,3,2,5};
    heapsort(a,15);
    return 0;
}
