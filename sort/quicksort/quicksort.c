//思想:
    //冒泡排序的加强版 
    //就是你 从数组中 任取一个元素 p (可随机取,现在以取第一个为例) 以P作为关键字,
    //对数组 进行划分 ,前一部分小于 P,后一部分 大于p 
    //最后 划分处 存储 p 
    //然后分别对划分后的前一部分 和 后一部分 递归调用 
    //算法平均时间复杂度: O(nlogn)
    //优点：是现在最快的排序算法
#include<stdio.h>

void quicksort(int a[], int left, int right);

void quicksortproxy(int a[], int n)
{
    quicksort(a, 0, 9);
}

// start end 表示排序的区间。
// 排序的最重要的思想就是缩短区间，每次把比关键词大的放在右边，把比关键词小的放在左边，一次一次的递归就可以了。
void quicksort(int a[], int left, int right)
{
    int i = left;
    int j = right;
    //每次都取第一个作为 关键词
    int key = a[left];
    //记录现在空位用的,这个p指针在快速排序中起到了至关重要的作用
    //每找到一个合适的值，就会更新之歌p指针。
    int p = left;
    printf("关键字为：%d时：排序结果为：\n", a[left]);
    while(i <= j) 
    {
        //从右边开始找，找到第一个比key小的值,
        while(j >= p && a[j] >= key) { j--; }
        //如果找到
        if (j >= p) 
        {
            a[p] = a[j];
            p = j;
        }

        //从左边开始找，找到第一个比key大的值,
        while(i <= p && a[i] <= key) { i++; }
        //如果找到
        if (i <= p) 
        {
            a[p] = a[i];
            p = i;
        }
    } 

    //最后弄完了就把最中间的元素换成key即可，自此所有的比key大的都在右边，比key小的都在左边
    a[p] = key; 
    for(int i = 0; i < 10; i++) { printf("%4d", a[i]); }
    printf("\n");
    //一次关键词完成后递归
    if(p - left > 1) { quicksort(a,left, p - 1); }
    if (right - p > 1) { quicksort(a, p + 1, right); }
}

int main()
{
    int a[10] = {10,9,8,7,6,5,4,3,2,1};
    quicksortproxy(a,10);

    for(int i = 0; i < 10; i++)
    {
        printf("%4d", a[i]);
    }
    printf("\n");
    return 0;

}
