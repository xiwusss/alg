#include<stdio.h>

typedef struct SBTNode
{
    struct SBTNode *left, *right;
    int key;
    int size;
}SBTNode, *SBTree;
void SBT_LeftRotate(SBTree *x)
{
    SBTree y = (*x)->right;
    (*x)->right = y->left;
    y->left = (*x);
    y->size =(*x)->size;
    (*x)->size = (!(*x)->left?0:(*x)->left->size) + (!(*x)->right?0:(*x)->right->size) + 1;
    (*x) = y;
}


int main()
{
    return 0;
}
