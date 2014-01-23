//各种树结构之 二叉排序树 ---------------- avl平衡二叉树 ------------------- 红黑树
#include<stdio.h>
#include<stdlib.h>

typedef struct Node
{
    int val;
    struct Node* l_child;
    struct Node* r_child;
    struct Node* parent;
} *BTree;

// insert 插入到正确的位置
//                                   50
//                                  /  \
//                                35    65
//                               / \    / \
//                              15 45  55  86
//                              /\         /\
//                             7 20       77 100  
//                          针对于上面，我要插入一个40，

void swap(BTree a, BTree b)
{
    int temp = a-> val;
    a-> val = b -> val;
    b -> val = temp;
}

BTree find(BTree root, int val)
{
    //首先找到这个元素，
    while(root != NULL && val != root->val)
    {
        if(root->val > val)//左边
            root = root->l_child;
        else//右边
            root = root->r_child;
    }
    return root;
}

//找到左子树中最大的元素,左边不为空的情况下，
BTree find_left_max(BTree node) 
{
    node = node->l_child;
    if(!node)
    {
        return NULL;
    }    
    while(node->r_child != NULL)
    {
        node = node->r_child;
    }
    return node;
}

//找到右子树中最小的元素
BTree find_right_min(BTree node) 
{
    node = node->r_child;
    if(!node)
    {
        return NULL;
    }
    while(node->l_child != NULL)
    {
        node = node->l_child;
    }
    return node;
}

BTree create_node(v)
{
    BTree p = (BTree)malloc(sizeof(struct Node));
    p->val = v;
    p->l_child = NULL;
    p->r_child = NULL;
    p->parent = NULL;
    return p;
}

BTree null_node = NULL;
BTree root_node = NULL;

//右边找到最小的。
BTree TreeMinimum(BTree x)
{
    while(x->l_child != null_node)
        x = x-> l_child;
    return x;
}

//获取某结点的后继
BTree TreeSuccessor(BTree x)
{
    if(x ->r_child == null_node)
        return x;
    return TreeMinimum(x->r_child);
}

BTree BTDelete(BTree z)
{
    BTree y,x;
    //y 记录要删除的节点, 没左孩子也没右孩子
    if(z->l_child == null_node || z->r_child == null_node)//要删除的是自己
        y = z;
    else 
        y = TreeSuccessor(z);
    
    //x,记录真正被删除元素的孩子节点。就是要升级的孩子节点。
    if(y->r_child != null_node)
        x = y->r_child;
    else
        x = null_node;

    x->parent = y->parent;
    //如果要删除的元素就是根元素
    if(y->parent == null_node)
        root_node = x; 
    else if(y == y->parent->l_child)//如果要删除的元素是父亲的左节点
        y->parent->l_child = x; 
    else//如果要删除的元素是父亲的右节点
        y->parent->r_child = x;

    if(y != z)
        z->val = y->val;
    //返回被删除的元素
    return y;
}

//删除稍微麻烦一些，做到这里，就会发现，我们缺一个指向父亲的指针，所有结构体中需要一个指向父亲节点的指针
BTree delete(BTree root, int val)
{
    BTree delete_node = find(root, val);
    if(!delete_node)
    {
        return NULL ;
    }
	return BTDelete(delete_node);
}

void insertOk(int val)
{
    BTree node = root_node;
    if(node == null_node)
    {
        BTree new_node = create_node(val); 
        node->l_child = new_node;
        new_node->l_child = new_node->r_child = null_node;
        new_node->parent = node;
        return;
    }
}

void insert(int val)
{
    BTree node = root_node;
    while(1)
    {
        if(node->val > val)//当前比插入的大，就去左边 
        {
            if(node->l_child != null_node)
            {
                node = node->l_child;
            }
            else
            {
                BTree new_node = create_node(val); 
                node->l_child = new_node;
                new_node->l_child = new_node->r_child = null_node;
                new_node->parent = node;
                break;
            }
        }
        else// 就去右边
        {
            if(node->r_child != null_node)
            {
                node = node->r_child;
            }
            else
            {
                BTree new_node = create_node(val); 
                node->r_child = new_node;
                new_node->l_child = new_node->r_child = null_node;
                new_node->parent = node;
                break;
            }
        }
    }
}

//递归 中序遍历
void print_tree_one(BTree root)
{
    if(root->l_child != null_node)
    {
        print_tree_one(root->l_child);
    }

    printf("%5d", root->val);

    if(root->r_child != null_node)
    {
        print_tree_one(root->r_child);
    }
}

//非递归, 中序遍历, 借用栈
void print_tree_two(BTree root)
{

}

int main()
{
    null_node = create_node(0);
    null_node->l_child = null_node;
    null_node->r_child = null_node;
    null_node->parent = NULL;

    root_node= create_node(50); 
    root_node->l_child = root_node->r_child = null_node;
    root_node->parent = NULL;

    insert(35);
    insert(65);
    insert(15);
    insert(45);
    insert(55);
    insert(86);
    insert(7);
    insert(20);
    insert(77);
    insert(100);
    //print_tree_one(root_node);
    //printf("\n");

    BTree y = delete(root_node, 45);
    printf("删除的元素是：%5d\n", y->val);
    BTree m = delete(root_node, 86);
    printf("删除的元素是：%5d\n", m->val);
    BTree k = delete(root_node, 77);
    printf("删除的元素是：%5d\n", k->val);

    print_tree_one(root_node);
}
