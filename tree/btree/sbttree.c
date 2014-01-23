#include<stdio.h>
#include<stlib.h>

typedef struct SBTNode
{
    struct SBTNode *left, *right;
    int key;
    int size;
}SBTNode, *SBTree;

// 左旋转：                     X 
//                           /     \
//                          B       Y    ---------------------------------------------         Y 
//                                /   \                                                      /    \
//                               D     E                                                    X      E
//                                                                                        /   \
//                                                                                       B    D

//以X为根节点进行旋转
void SBT_LeftRotate(SBTree *x)
{
    SBTree y = (*x)->right;
    (*x)->right = y->left;
    y->left = (*x);
    y->size =(*x)->size;
    (*x)->size = (!(*x)->left?0:(*x)->left->size) + (!(*x)->right?0:(*x)->right->size) + 1;
    (*x) = y;
}

// 右旋转：              
//                       
//                               X                                 Y         
//                            /    \                            /     \
//                           Y      E   ----------------       B        X    
//                         /   \                                      /   \
//                        B    D                                     D     E 

//以X为根节点进行旋转
void SBT_RightRotate(SBTree *x)
{
    SBTree y = (*x)->left;
    (*x)->left = y->right;
    y->right = (*x);
    y->size =(*x)->size;
    (*x)->size = (!(*x)->left?0:(*x)->left->size) + (!(*x)->right?0:(*x)->right->size) + 1;
    (*x) = y;
}



//

void SBT_Maintain(SBTree &x, bool flag)
{
    if((*x) == NULL)
        return;
 //四种情况，要么1，3 要么2， 4 
    //case 1: S[A] > S[R] 
    //
    //                     T
    //                  /     \
    //                 L       R
    //               /   \    /  \
    //              A     B  C    D
    // 一： 右旋转 SBT_RightRotate(T)
    //                     L
    //                  /     \
    //                 A       T 
    //                        /  \
    //                        B    R
    //                           /  \
    //                          C    D 
    //
    // 二： Maintain(T)
    // 三： Maintain(L)
    
    //Case2. s[B] > S[R]
    //
    //                     T
    //                  /     \
    //                 L       R
    //               /   \    /  \
    //              A     B  C    D
    //                   / \
    //                  E   F
    // 一： 左旋转 SBT_LeftRotate(L)
    // 二： 右旋转 SBT_RightRotate(T)
    // 三： Maintain(L) & Maintain(T)
    // 四： Maintain(B) 
    
    //case 3 和 case 4 和 case 1 和case 2 完全对称
    //case 3: S[D] > S[L] 
    // 一： 左旋转 SBT_RightRotate(T)
    // 二： Maintain(T)
    // 三： Maintain(L)
 
    //Case4. s[C] > S[L]
    // 一： 右旋转 SBT_RightRotate(R)
    // 二： 左旋转 SBT_LeftRotate(T)
    // 三： Maintain(R) & Maintain(T)
    // 四： Maintain(C) 
    
    if(!flag) //在左边插入的时候
    {
        //case 3
        if((*x)->left && (*x)->left->left && (!(*x)->right) || (*x) ->left->left->size > (*x->right->size))
        {
            SBT_RightRotate(x);
        }else if((*x)->left && (*x)->left->right &&(!(*x)->right||(*x)->left->right->size > (*x)->right->size))//case2
        {
            SBT_LeftRotate((*x)->left);
            SBT_RightRotate((*x));
        }
        else
            return;
    }
    else
    {
        
    }

} 

void SBT_Insert(SBTree *x,  int key)
{
    if((*x) == NULL)
    {
        SBTree new_node = (SBTree) malloc(sizeof(SBTNode));
        new_node -> key = key;
        new_node -> size = 1 ;
        new_node -> left = new_node->right = NULL;
        (*x) = new_node;
    }
    SBT_Insert(key <= (*x) -> key ? (*x) -> left : (*x) -> right, x);
    SBT_Maintain(x, key > (*x) -> key);
}

int main()
{
    return 0;
}
