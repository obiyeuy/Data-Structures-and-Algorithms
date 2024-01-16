// 设树的结点为char类型，请用左孩子右兄弟表示法建树,并完成遍历等操作。

// 1，以二元组(fa,ch)的形式自上而下、自左而右依次输入树的各边，建立树的孩子-兄弟链表，fa表示ch的父亲，ch是fa的孩子。

// 2，输出树的先序遍历结果

// 3，输出树的后序遍历结果

// 4，输出树的深度

// 5，输出树中叶子结点的数量

// 6，输出树中从根到叶子的路径

// 针对如下所示的树T

#include <stdlib.h>
#include <stdio.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode *child;
    struct TreeNode *brother;
} TreeNode;

typedef struct QueueNode
{
    TreeNode *data;
    struct QueueNode *next;
} QueueNode;

typedef struct StackNode
{
    TreeNode *data;
    struct StackNode *next;
} StackNode;

StackNode *initStack()
{
    StackNode *S = (StackNode *)malloc(sizeof(StackNode));
    S->data = 0;
    S->next = NULL;
    return S;
}

int isEmptyStack(StackNode *S)
{
    if (S->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

TreeNode *top(StackNode *S)
{
    if (isEmptyStack(S))
    {
        return NULL;
    }
    else
    {
        return S->next->data;
    }
}

TreeNode *pop(StackNode *S)
{
    if (isEmptyStack(S))
    {
        return NULL;
    }
    else
    {
        StackNode *node = S->next;
        TreeNode *data = node->data;
        S->next = node->next;
        return data;
    }
}

void push(StackNode *S, TreeNode *data)
{
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->data = data;
    node->next = S->next;
    S->next = node;
}

void printStack(StackNode *S)
{
    StackNode *node = S->next;
    while (node)
    {
        printf("%c", node->data->data);
        node = node->next;
    }
}

QueueNode *initQueue()
{
    QueueNode *Q = (QueueNode *)malloc(sizeof(QueueNode));
    Q->data = NULL;
    Q->next = NULL;
    return Q;
}

int isEmpty(QueueNode *Q)
{
    if (Q->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void enQueue(QueueNode *Q, TreeNode *data)
{
    QueueNode *q = Q;
    QueueNode *node = (QueueNode *)malloc(sizeof(QueueNode));
    node->data = data;
    node->next = NULL;
    while (q->next != NULL)
    {
        q = q->next;
    }
    q->next = node;
}

TreeNode *deQueue(QueueNode *Q)
{
    if (isEmpty(Q))
    {
        return NULL;
    }
    else
    {
        QueueNode *node = Q->next;
        TreeNode *data = node->data;
        Q->next = node->next;
        return data;
    }
}

TreeNode *topQueue(QueueNode *Q)
{
    if (isEmpty(Q))
    {
        return NULL;
    }
    else
    {
        return Q->next->data;
    }
}

TreeNode *initTree(char data)
{
    TreeNode *T = (TreeNode *)malloc(sizeof(TreeNode));
    T->data = data;
    T->brother = NULL;
    T->child = NULL;
    return T;
}

// 树的先序就是二叉树的先序
void preOrder(TreeNode *T)
{
    if (T)
    {
        if (T->data != '/')
        {
            printf("%c", T->data);
        }

        preOrder(T->child);
        preOrder(T->brother);
    }
}

// 树的后序就是二叉树的中序
void postOrder(TreeNode *T, TreeNode *tmp)
{
    if (T)
    {
        postOrder(T->child, tmp);
        if (T->data != '/')
        {
            printf("%c", T->data);
        }
        postOrder(T->brother, tmp);
    }
}

// 树的层序遍历与二叉树的层序遍历相似，但树遍历时是将左子树以及左子树的右子树加入队列
void level(TreeNode *T, QueueNode *Q)
{
    enQueue(Q, T);
    TreeNode *tmp;
    while (!isEmpty(Q))
    {
        tmp = deQueue(Q);
        if (tmp->data != '/')
        {
            printf("%c", tmp->data);
        }
        if (tmp->child)
        {
            enQueue(Q, tmp->child);
            tmp = tmp->child;
            while (tmp->brother != NULL)
            {
                enQueue(Q, tmp->brother);
                tmp = tmp->brother;
            }
        }
    }
}

int depth(TreeNode *T)
{
    if (!T)
    {
        return -2;
    }
    else
    {
        int left = depth(T->child) + 1;
        int right = depth(T->brother);
        return left > right ? left : right;
    }
}

void countLeaf(TreeNode *T, int &count)
{
    if (T)
    {
        if (T->child == NULL)
        {
            count++;
        }
        countLeaf(T->child, count);
        countLeaf(T->brother, count);
    }
}

/*输出树中每一条从根结点到叶子节点的路径*/
void allPath(TreeNode *T, StackNode *S)
{
    while (T)
    {
        push(S, T);
        if (T->child)
            allPath(T->child, S);
        else
        {
            StackNode *tmp = initStack();
            StackNode *node = S->next;
            while (node)
            {
                if (node->data->data != '/')
                {
                    push(tmp, node->data);
                }
                node = node->next;
            }
            printStack(tmp);
            printf("\n");
        }
        pop(S);
        T = T->brother;
    }
}

int main()
{
    TreeNode *T;
    char left = 0;
    char right = 0;
    int count = 0;
    QueueNode *Q = initQueue();
    char str[3];
    scanf("%s", str);
    left = str[0];
    right = str[2];
    if (right == '#')
    {
        return 0;
    }
    else
    {
        T = initTree(right);
        enQueue(Q, T);
    }
    TreeNode *tmp = T;
    TreeNode *br;
    scanf("%s", str);
    left = str[0];
    right = str[2];
    while (right != '#')
    {
        if (left != topQueue(Q)->data)
        {
            deQueue(Q);
            tmp = topQueue(Q);
            count = 0;
        }
        else if (count == 0)
        {
            tmp->child = initTree(right);
            enQueue(Q, tmp->child);
            tmp = tmp->child;
            br = tmp;
            count++;
            scanf("%s", str);
            left = str[0];
            right = str[2];
        }
        else
        {
            br->brother = initTree(right);
            enQueue(Q, br->brother);
            br = br->brother;
            count++;
            scanf("%s", str);
            left = str[0];
            right = str[2];
        }
    }
    preOrder(T);
    printf("\n");
    postOrder(T, T);
    printf("\n");
    QueueNode *Q1 = initQueue();
    level(T, Q1);
    printf("\n");
    printf("%d\n", depth(T) + 1);
    int count1 = 0;
    countLeaf(T, count1);
    printf("%d\n", count1);
    StackNode *S = initStack();
    allPath(T, S);
    return 0;
}