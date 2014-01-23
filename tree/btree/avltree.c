//平衡树的最大的难点就是在 二叉排序树的基础上保持平衡。
//这里面最重要的概念就是 旋转，
//旋转分为四种 左左， 左右， 右右， 右左, 两两对称
//                    6
//                  /    \
//                 3      7
//               /  \
//              1     4
//               \
//                2
//                左左 
//                
//           从6这里开始，就失去了平衡，6的左边比右边高2，而出现问题是在6左边的左边,所有叫左左
//
//                    6
//                  /    \
//                 2      7
//               /   \
//              1     4
//                   / 
//                  3
//             
//                左右
//
//           从6这里开始，就失去了平衡，6的左边比右边高2，而出现问题是在6左边的右边,所有叫左右
//
//
//                 2 
//               /   \
//              1     5
//                  /   \
//                3      6
//                 \
//                  4
//                右左               
//
//           从2这里开始，就失去了平衡，2的右边比左边高2，而出现问题是在2右边的左边,所有叫右左
//
//
//                 2 
//               /   \
//              1     4
//                  /   \
//                3      6
//                      / 
//                     5
//                右右                             
//
//           从2这里开始，就失去了平衡，2的右边比左边高2，而出现问题是在2右边的右边,所有叫右右

#include<stdio.h>
#include<stdlib.h>

typedef struct TreeNode
{
    int val;
    int hgt;
    int fre; //记录相等的元素。
    struct TreeNode* lson;
    struct TreeNode* rson;

}*AVLTree;

//计算以此节点为root的树的高度
int height(AVLTree node)
{
    if(node != NULL)
    {
        return node->hgt;
    }
    return -1;
}

//返回两个整数的较大者
int max(int a, int b)
{
    return a > b ? a : b;
}

//针对与左左的情况，单旋转方式：如下
//                    k2                                                             
//                  /    \
//                 k1     7                                              k1 
//               /  \                 -----------旋转--------------    /     \
//              1     4                                              1        k2     
//               \                                                    \      / \
//                2                                                    2    4   7   
//                左左

AVLTree root_node;

//左左，
AVLTree sing_rotate_left(AVLTree k2)
{
    
    AVLTree k1 = k2->lson;
    k2->lson = k1->rson;
    k1->rson = k2;
    k2->hgt = max(height(k2->lson),height(k2->rson)) + 1;
    k1->hgt = max(height(k1->lson),k2->hgt) + 1;
    return k1;
}
//
//针对与右右的情况，单旋转方式：如下
//                 k2 
//               /   \
//              1     k1                                                   k1
//                  /   \             -----------旋转--------------      /     \
//                3      6                                              k2       6  
//                      /                                             /   \     /
//                     5                                              1   3    5
//                右右                 
//

//右右, 和左左是对应的。
AVLTree sing_rotate_right(AVLTree k2)
{
    AVLTree k1 = k2->rson;
    k2->rson = k1->lson;
    k1->lson = k2;
    k2->hgt = max(height(k2->lson),height(k2->rson)) + 1;
    k1->hgt = max(height(k1->rson),k2->hgt) + 1;

    return k1;
}

//左右， 双旋转
//
//                    k3                                                                                    
//                  /    \                                                       k3                                                                                 
//                 k1      7                                                   /    \
//               /   \                                                        k2     7                                                          k2   
//              1     k2    ---旋转第一步-把k1作为根，进行一次右右旋转---  /    \          ---旋转第一步-把k3作为根，进行一次左左旋转---      /     \
//                  /   \                                                 k1     5                                                          k1       k3  
//                3      5                                               /   \                                                             /   \    /  \
//                左右                                                  1     3                                                           1     3  5    7

AVLTree double_rotate_lr(AVLTree k3)
{
    k3->lson = sing_rotate_right(k3->lson);
    return sing_rotate_left(k3);
}

//右左， 双旋转
//
//                    k3                                                                                    
//                  /    \                                                           k3                                                                                 
//                 1      k1                                                       /    \
//                       /  \                                                     1      k2                                                               k2   
//                     k2    7   ---旋转第一步-把k1作为根，进行一次左左旋转---          /   \      ---旋转第一步-把k3作为根，进行一次右右旋转---        /     \
//                   /   \                                                            3     k1                                                        k3       k1  
//                 3      5                                                               /    \                                                     /   \    /  \
//                左右                                                                   5      7                                                   1     3  5    7

AVLTree double_rotate_rl(AVLTree k3)
{
    k3->rson = sing_rotate_left(k3->rson);
    return sing_rotate_right(k3);
}

//这里有一个难点，就是返回值，
//我们返回了AVLTree其实就是根元素。
// 
// PS1：  root->lson = insert(root->lson, val);
//       root->rson = insert(root->rson, val); 
// 在这里非常重要，把下一层插入的地方返回后。我就把我自己的左边或者右边返回给上层
//
// PS2： 难点
// root = sing_rotate_left(root);
// root = double_rotate_lr(root);
// root = sing_rotate_right(root); 
// root = double_rotate_rl(root);
//
// 插入成功后， 如果当前节点的左边 和右边的高度差值为2的时候，进行旋转。
// 旋转完了后把当前的旋转后新的root返回，
// 那么根据上面的insert 中 lson -> insert() 或者 rson -> insert() 就可以自动赋值给左或者右孩子，这是递归的作用。
AVLTree insert(AVLTree root, int val)
{
    if(root == NULL) //如果节点为空，那么就在这里插入
    { 
        root = (AVLTree)malloc(sizeof(struct TreeNode));
        root->val = val;
        root->lson = NULL;
        root->rson = NULL;
        root->hgt = 0;
        return root;
    } 
    if(root->val > val) //左边
    {
        root->lson = insert(root->lson, val); //插入成功后，就开始判断插入后，会不会影响平衡，如果影响，那么就进行调整 
        if(height(root->lson) - height(root->rson) == 2)
        {
            //判断这里应该是l旋转 还是 lr
            if(root->lson->val > val) //ll,可以参考上面的图就知道了。
            {
                root = sing_rotate_left(root); 
            }
            else
            {
                root = double_rotate_lr(root);
            }
        }
    }
    else if(root -> val < val) //右边
    {
        root->rson = insert(root->rson, val); //插入成功后，就开始判断插入后，会不会影响平衡，如果影响，那么就进行调整 
        if(height(root->rson) - height(root->lson) == 2)
        {
            //判断这里应该是l旋转 还是 lr
            if(root->rson->val < val) //rr,可以参考上面的图就知道了。
            {
                root = sing_rotate_right(root); 
            }
            else
            {
                root = double_rotate_rl(root);
            }
        }
    }
    else //等于
    {
        root->fre += 1;        
    }
    //更新插入后，受影响的节点的高度
    root->hgt = max(height(root->lson), height(root->rson)) + 1;
    return root;
}

AVLTree find(AVLTree root, int val)
{
    if(root == NULL)
    {
        return NULL;
    }

    if (root->val > val)
    {
        find(root->lson, val);
    }
    else if(root->val < val)
    {
        find(root->rson, val);
    }
    else
    {
        return root;
    }
}

void print_AVL_tree(AVLTree root)
{
    if(root == NULL)
    {
        return ;
    }  

    print_AVL_tree(root->lson);
    printf("%5d", root->val);
    print_AVL_tree(root->rson);
}

AVLTree find_min(AVLTree root)
{
    if(root->lson == NULL)
    {
        return root;
    }
    return find_min(root->lson);
}

AVLTree delete(AVLTree root, int val)
{
   if(root == NULL)
    {
        return NULL;
    }

    if(root->val == val)
    {
        if(root->fre > 1)//如果删除的元素存在多个，那么就把fre -1
        {
            root->fre -= 1;
        }
        else
        {
            //两个孩子都存在的情况下
            if(root->lson != NULL && root->rson != NULL)
            {
                //去右子树中找到最小的节点
                root->val = find_min(root->rson)->val;
                //删除右子树的指定元素
                root->rson = delete(root->rson, root->val);
            }
            else
            {
                //存在一个孩子或者不存在孩子的情况下，
                AVLTree temp = root;
                root = root->lson == NULL ? root->lson : root->rson;
                //如果两个孩子都不存在
                if(root == NULL)
                {
                    return NULL;
                }
                free(temp);
            }
        }
    }
    else if(root->val > val) //左边
    {
       root->lson = delete(root->lson, val); 
        //判断是否需要旋转，这里已经是删除成功了,已经返回了。
        if(height(root->lson) - height(root->rson) == 2)
        {
            //说明是左左
            if(root->lson->val > val)
            {
               root = sing_rotate_left(root); 
            }
            else
            {
                root = double_rotate_lr(root);
            }
        }
    }
   else //右边
   {
       root->rson = delete(root->rson, val); 
       //判断是否需要旋转，这里已经是删除成功了,已经返回了。
       if(height(root->rson) - height(root->lson) == 2)
       {
           //说明是右右
           if(root->rson->val < val)
           {
               root = sing_rotate_right(root); 
           }
           else
           {
               root = double_rotate_rl(root);
           }
       }

   }
    //删除成功后，重新更新高度
    root->hgt = max(height(root->lson), height(root->rson)) + 1;
    return root;
}

int main()
{
    AVLTree root = (AVLTree)malloc(sizeof(struct TreeNode));
    root->val = 4;
    root->lson = NULL;
    root->rson = NULL;
    root->hgt = 0;
    root_node = insert(root, 5);
    root_node = insert(root_node, 7);
    root_node = insert(root_node, 3);
    root_node = insert(root_node, 2);
    root_node = insert(root_node, 2);
    root_node = insert(root_node, 6);
    root_node = insert(root_node, 1);
    root_node = insert(root_node, 9);
    root_node = insert(root_node, 10);
    root_node = insert(root_node, 11);

    print_AVL_tree(root_node);
    printf("\n");
    root_node = delete(root_node, 10);
    print_AVL_tree(root_node);
    return 0;
}
