#include <stdlib.h>
#include <stdio.h>

typedef struct TreeNode
{
    char data;
    int ltag, rtag;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode;

void createTree(TreeNode **T, char *data, int *index)
{
    char ch;
    ch = data[*index];
    *index += 1;
    if (ch == '#')
    {
        *T = NULL;
    }
    else
    {
        *T = (TreeNode *)malloc(sizeof(TreeNode));
        (*T)->data = ch;
        (*T)->ltag = 0;
        (*T)->rtag = 0;
        createTree(&((*T)->lchild), data, index);
        createTree(&((*T)->rchild), data, index);
    }
}

void preThread(TreeNode *&T, TreeNode *&pre)
{
    if (T)
    {
        if (T->lchild == NULL)
        {
            T->lchild = pre;
            T->ltag = 1;
        }
        if (pre != NULL && pre->rchild == NULL)
        {
            pre->rchild = T;
            pre->rtag = 1;
        }
        pre = T;
        if (T->ltag == 0)
        {
            preThread(T->lchild, pre);
        }
        preThread(T->rchild, pre);
    }
}

// TreeNode *getNext(TreeNode *node)
// {
//     if (node->rtag == 1)
//     {
//         return node->rchild;
//     }
//     else
//     {
//         return node->lchild;
//     }
// }

// 为线索二叉树添加头结点，使之可以双向操作
void InOrderThreading(TreeNode *&Thrt, TreeNode *&T)
{
    Thrt = (TreeNode *)malloc(sizeof(TreeNode)); // 开辟结点
    Thrt->ltag = 0;
    Thrt->rtag = 1;      // 设置标志域
    Thrt->rchild = Thrt; // 右结点指向本身
    if (!T)
    {
        Thrt->lchild = Thrt;
        return; // 若根结点不存在,则该二叉树为空,让该头结点指向自身.
    }
    TreeNode *pre; // 设置前驱结点
    // 令头结点的左指针指向根结点
    pre = Thrt;
    Thrt->lchild = T;
    // 开始递归输入线索化
    InOrderThreading(T, pre);
    // 此时结束了最后一个结点的线索化了,下面的代码把头结点的后继指向了最后一个结点.
    // 并把最后一个结点的后继也指向头结点,此时树成为了一个类似双向链表的循环.
    pre->rchild = Thrt;
    pre->rtag = 1;
    Thrt->rchild = pre;
}
// 非递归遍历线索二叉树
void InOrderTraverse(TreeNode *T)
{
    TreeNode *p = T->lchild;
    while (p != T)
    {
        while (p->ltag == 0)
            p = p->lchild; // 走向左子树的尽头
        printf("%c", p->data);
        while (p->rtag == 1 && p->rchild != T)
        { // 访问该结点的后续结点
            p = p->rchild;
            printf("%c", p->data);
        }
        p = p->rchild;
    }
}

TreeNode *getNext(TreeNode *node)
{
    if (node->rtag == 1 || node->ltag == 1)
    {
        return node->rchild;
    }
    else
    {
        return node->lchild;
    }
}

int main()
{
    TreeNode *T;
    TreeNode *pre = NULL;
    // char data[] = "AB##C##";
    char data[] = "ABD##E##CF##G##";
    int index = 0;
    createTree(&T, data, &index);
    // InOrderThreading(T, pre);
    // InOrderTraverse(T);
    preThread(T, pre);
    // pre->rtag = 1;   ????
    // pre->rchild = NULL;
    for (TreeNode *node = T; node != NULL; node = getNext(node))
    {
        printf("%c ", node->data);
    }
    return 0;
}