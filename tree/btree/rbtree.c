// 红黑树， 二叉排序树BST-------> 二叉平衡树AVL -------> RBTREE
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef enum Color{RED, BLACK} Color;
typedef int ElementType; 

typedef struct Node
{
    ElementType val;
    struct Node* left;
    struct Node* right;
    struct Node* parent;
    Color color;
}*Position;

Position null_node = NULL;
Position root_node = NULL;

//
//                                k2
//                              /   \
//                             k1     叔                                                   
//                          /     \             -------------------                          k1  
//                         新      3                                                      /      \
//                       /   \                                                           新       k2  
//                      1     2                                                        /   \     /   \
//                                                                                    1     2   3      叔
//左左旋转
void single_left_rotate(Position k2)
{
    Position k1 = k2->left;
    k2->left = k1->right;
    //这个比AVL树旋转稍微复杂一些，因为父亲指针需要更新
    if(k1->right != null_node)
    {
        k1->right->parent = k2;
    }

    k1->parent = k2->parent;

    if(k2->parent == null_node)
    {
        root_node = k1;
        root_node->parent = null_node;
    }
    else
    {
        if(k2 == k2->parent->left)
        {
           k2 ->parent->left = k1; 
        }
        else
        {
            k2->parent->right = k1;
        }
    }
    k1->right = k2;
    k2->parent = k1;
}

//右右旋转
void single_right_rotate(Position k2)
{
    Position k1 = k2->right;
    k2->right = k1->left;
    //这个比AVL树旋转稍微复杂一些，因为父亲指针需要更新
    if(k1->left != null_node)
    {
        k1->left->parent = k2;
    }

    k1->parent = k2->parent;

    if(k2->parent == null_node)
    {
        root_node = k1;
        root_node->parent = null_node;
    }
    else
    {
        if(k2 == k2->parent->left)
        {
           k2 ->parent->left = k1; 
        }
        else
        {
            k2->parent->right = k1;
        }
    }
    k1->left = k2;
    k2->parent = k1;
}


//左右旋转
void double_rotate_lr(Position k2)
{
    single_right_rotate(k2->left);
    single_left_rotate(k2);
}

//右左旋转
void double_rotate_rl(Position k2)
{
    single_left_rotate(k2->right);
    single_right_rotate(k2);
}

//插入完成后，调整性质
void RBTInsertFixup(Position z)
{
    while(z->parent->color == RED)// 根据父亲颜色的回溯
    {
        //父亲如果是左孩子 只会出现 左左旋转 和 左右旋转
        if(z->parent == z->parent->parent->left)
        {
            Position y = z->parent->parent->right;//叔叔
            if(y->color == RED) //红叔,不需要旋转
            {
                y->color = BLACK;
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else//黑叔,需要旋转, 旋转完成后，新的根都是黑色，没有必要回溯了,就是在这里比avl树快的原因
            {
               if(z == z->parent->left)// 左左旋转
                {
                    single_left_rotate(z->parent->parent);
                    //旋转结束后，修改颜色
                    z->parent->color = BLACK;
                    z->parent->right->color = RED;
                }
                else //左右旋转
                {
                    double_rotate_lr(z->parent->parent);
                    z->right->color = RED;
                    z->color = BLACK;
                }
                return ;
            }
        }
        else//父亲如果是右孩子 只会出现 右右旋转 和 右左旋转
        {
            Position y = z->parent->parent->left;//叔叔
            if(y->color == RED) //红叔,不需要旋转
            {
                y->color = BLACK;
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else//黑叔,需要旋转
            {
               if(z == z->parent->right)// 右右旋转
                {
                    single_right_rotate(z->parent->parent);
                    //旋转结束后，修改颜色
                    z->parent->color = BLACK;
                    z->parent->left->color = RED;
                }
                else //右左旋转
                {
                    double_rotate_rl(z->parent->parent);
                    z->left->color = RED;
                    z->color = BLACK;
                }
                return ;
            }
        }
    } 
    //最后修改根为黑色
    root_node -> color = BLACK;
}
//6种情况，
// 1. 黑父，最简单，插入即可
// 2. 红父，五种情况
// 2.1 红叔，在这五种情况下，这一种最简单
// 2.2 黑叔， 存在四种情况，
// 2.2.1 左左旋转
// 2.2.2 左右旋转 
// 2.2.3 右右旋转
// 2.2.4 右左旋转 

//Node结构的parent成员指向父结点, 
//color指出该结点的颜色. 
//在上面我们还增加一个全局的空结点NullNode, 
//空结点将在初始化时被创建, 
//该空结点的左右子树指向自身,且颜色为黑. 
//当创建一个新结点时, 我们总是将新结点的左右子树指向它. 
//另外我们维护一个指向根结点的指针RootNode, 并且我们还设定根结点的父结点也指向NullNode. 
Position create_node(v)
{
    Position p = (Position)malloc(sizeof(struct Node));
    p->val = v;
    p->left = NULL;
    p->right = NULL;
    p->color = RED;
    return p;
}

void RBTInsert(ElementType v)
{
    Position z,y,x;
    y = null_node;
    x = root_node;
    z = create_node(v);
    //首先找到要插入的位置
    while(x != null_node)
    {
        //这里的目的是为了记录下要插入的元素的父亲是谁
        y = x;
        if(z->val < x->val)//左边
            x = x->left;
        else //右边
            x = x->right;
    }
    z->parent = y;
    z->left = z->right = null_node;
    z->color = RED;
    if(y == null_node)// 最开始一个元素都没有的情况下
    {
        root_node = z;
        root_node->parent = null_node;
        root_node->color = BLACK;
        return;
    } 
    //根据插入的位置决定他是父亲的左孩子还是右孩子
    if(z->val < y->val)
        y->left = z;
    else
        y->right = z;
    //向上进行调整
    //1.如果是黑父，这是最简单的情况，不需要调整
    //2红父
    if(z->parent->color == RED)
    {
       RBTInsertFixup(z);       
    }
}

//右边找到最小的。
Position TreeMinimum(Position x)
{
    while(x->left != null_node)
        x = x-> left;
    return x;
}

//获取某结点的后继
Position TreeSuccessor(Position x)
{
    if(x ->right == null_node)
        return x;
    return TreeMinimum(x->right);
}

Position RBTDeleteFixup(Position x)//升级的那个节点,也就是真正被删除的节点的孩子节点
{
	
	Position w;
	while(x != root_node && x->color == BLACK)
	{
		if(x == x->parent->left)//升级节点是左孩子
		{
			w = x->parent->right;
			/*Case1 红兄*/
			if(w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				//右右旋转
				single_right_rotate(x->parent);
				w = x->parent->right;
			}
			//红兄的情况需要进行RR或LL型旋转，然后将父结点染成红色，兄结点染成黑色。
			//然后重新以新点为判定点进行平衡操作。
			//我们可以观察到，旋转操作完成后，判定点没有向上回溯，而是降低了一层，此时变成了黑兄的情况。
			/*Case2*/
			//黑兄的情况最为复杂，需要根据黑兄孩子结点（这里用“侄”表示）和父亲结点的颜色来决定做什么样的操作。 
			//3.2.1 黑兄二黑侄红父
			if(w->left->color == BLACK && w->right->color==BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else/*Case3*/ // 3.2.2 黑兄红侄
			{
				if(w->right->color == BLACK)
				{
					w->left->color = BLACK;
					w->color = RED;
					//左左旋转
					single_left_rotate(w);
					w = x->parent->right;
				}
				/*Case4*/ 
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->right->color = BLACK;
				single_right_rotate(x->parent);
				x = root_node;
			}
		}
		else//升级节点是右孩子
		{
			w = x->parent->left;
			/*Case5 */
			if(w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				//左左旋转
				single_left_rotate(x->parent);
				w = x->parent->left;
			}
			/*Case6 */ //3.2.1 黑兄二黑侄红父
			if(w->left->color == BLACK && w->right->color==BLACK)
			{
				w->color = RED;
				x = x->parent;
			}
			else/*Case7*/ // 3.2.2 黑兄红侄
			{
				if(w->left->color == BLACK)
				{
					w->right->color = BLACK;
					w->color = RED;
					//youyou旋转
					single_right_rotate(w);
					w = x->parent->left;
				}
				/*Case8*/ 
				w->color = x->parent->color;
				x->parent->color = BLACK;
				w->left->color = BLACK;
				single_left_rotate(x->parent);
				x = root_node;
			}
		}
	}
}

Position find(Position root, int val)
{
    //首先找到这个元素，
    while(root != NULL && val != root->val)
    {
        if(root->val > val)//左边
            root = root->left;
        else//右边
            root = root->right;
    }
    return root;
}

//删除，最为麻烦。
Position RBTDelete(int val)
{
	Position z = find(root_node, val);
	Position y,x;
	//y 记录要删除的节点, 没左孩子也没右孩子
	if(z->left == null_node || z->right == null_node)//要删除的是自己
		y = z;
	else 
		y = TreeSuccessor(z);

	//x,记录真正被删除元素的孩子节点。就是要升级的孩子节点。
	if(y->right != null_node)
		x = y->right;
	else
		x = null_node;

	x->parent = y->parent;
	//如果要删除的元素就是根元素
	if(y->parent == null_node)
		root_node = x; 
	else if(y == y->parent->left)//如果要删除的元素是父亲的左节点
		y->parent->left = x; 
	else//如果要删除的元素是父亲的右节点
		y->parent->right = x;

	if(y != z)
		z->val = y->val;

	//这里就是最麻烦的开始。要删除的元素是红节点，最简单，不考虑调整,删除的元素是黑色，
	if(y->color == BLACK)
		RBTDeleteFixup(x);

	//返回被删除的元素
	return y;
}

void print_RBT_tree(Position root)
{
	if(root == null_node)
		return ;
	print_RBT_tree(root->left);
	printf("%5d", root->val);
	print_RBT_tree(root->right);
}

int main()
{
	null_node = create_node(0);
	null_node->left = null_node;
	null_node->right = null_node;
	null_node->parent = NULL;
	null_node->color = BLACK;
	root_node = null_node;
    /*
	RBTInsert(100);
	RBTInsert(150);
	RBTInsert(55);
	RBTInsert(12);
	RBTInsert(9);
	RBTInsert(110);
	RBTInsert(190);
	RBTInsert(5);
	RBTInsert(11);
	RBTInsert(35);
	RBTInsert(75);
    */
    int i;
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("\007The current date/time is: %s",asctime(timeinfo));

    for(i = 1; i < 5000000; i++)
    {
        RBTInsert(5000000 - i);
        RBTInsert(5000000 + i);
    }

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("\007The current date/time is: %s",asctime(timeinfo));
    //time ( &rawtime  ); -- 获取时间，以秒计，从1970年1月一日起算，存于rawtime
    //localtime ( &rawtime  ); -- 转为当地时间，tm 时间结构
    //asctime （）-- 转为标准ASCII时间格式：
    //星期 月 日 时：分：秒 年

    for(i = 1; i < 5000000; i++)
    {
        RBTDelete(i);
    }

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    printf("\007The current date/time is: %s",asctime(timeinfo));

    return 0;
}
