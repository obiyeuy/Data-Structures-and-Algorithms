// 平衡二叉树
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    int height;  //????? 必须要有 相当于在初始化时就有高度，单独计算高度需要在建好后，不适用于此处
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode;

int getHeight(TreeNode *node)
{
    return node?node->height:0;
}

int max(int a,int b){
    return a>b?a:b;
}
// RR型 右单旋
//  右右型：插入节点在不平衡因子节点右子树的右边
//  右单旋：向左旋转
//  取中间的节点，使它的父亲成为它的左孩子，如果它有左孩子的话，那么这个左孩子连接到父亲的右孩子上
void rrRotation(TreeNode *node, TreeNode **root)
{
    TreeNode *tmp = node->rchild;
    node->rchild = tmp->lchild;
    tmp->lchild = node;
    node->height = 1+max(getHeight(node->lchild),getHeight(node->rchild));
    tmp->height = 1+max(getHeight(tmp->lchild),getHeight(tmp->rchild));
    *root = tmp;
}

// LL型 左单旋
// 左左型：插入节点在不平衡因子节点的左子树的左边
// 左单旋：向右旋转
// 取中间的节点，使它的父亲成为它的右孩子，如果它有右孩子的话，那么这个右孩子连接到父亲的左孩子上
void llRotation(TreeNode *node, TreeNode **root)
{
    TreeNode *tmp = node->lchild;
    node->lchild = tmp->rchild;
    tmp->rchild = node;
    node->height = 1+max(getHeight(node->lchild),getHeight(node->rchild));
    tmp->height = 1+max(getHeight(tmp->lchild),getHeight(tmp->rchild));
    *root = tmp;
}

// RL型 右左双旋
// 右左型：插入节点在不平衡因子节点的右子树的左边
// 右左双旋：先以不平衡因子的右子树为支点进行右旋，再以不平衡因子节点为支点进行左旋
// 取最后一个节点，作为父亲节点，将它原先的父亲作为自己的右孩子，将父亲的父亲作为自己的左孩子
// 如果它有左孩子或者右孩子的话，它原先的左孩子连接到父亲的父亲的右孩子上；它原先的右孩子连接到父亲的左孩子上


// LR型 左右双旋
// 左右型：插入节点在不平衡因子节点的左子树的右边
// 左右双旋：先以不平衡因子的左子树为支点进行左旋，再以不平衡因子节点为支点进行右旋
// 取最后一个节点，作为父节点，将它的父亲作为自己的左孩子，将它的父亲的父亲作为自己的右孩子
// 如果它有左孩子或者右孩子的话，它原先的左孩子，连接到父亲的右孩子上；它原先的右孩子，连接到父亲的父亲的左孩子上

void avlInsert(TreeNode **T, int data)
{
    if (*T == NULL)
    {
        *T = (TreeNode *)malloc(sizeof(TreeNode));
        (*T)->data = data;
        (*T)->height = 0;
        (*T)->lchild = NULL;
        (*T)->rchild = NULL;
    }
    else if (data < (*T)->data)
    {
        avlInsert(&((*T)->lchild), data);
        int lHigth = getHeight((*T)->lchild);
        int rHight = getHeight((*T)->rchild);
        // 判断高度差
        if (lHigth - rHight == 2)
        {
            if (data < (*T)->lchild->data)
            {
                //LL调整
                llRotation(*T, T);
            }
            else  //LR调整
            {
                rrRotation((*T)->lchild, &((*T)->lchild));
                llRotation(*T, T);
            }
        }
    }
    else
    {
        avlInsert(&((*T)->rchild), data);
        int lHigth = getHeight((*T)->lchild);
        int rHight = getHeight((*T)->rchild);
        if (rHight - lHigth == 2)
        {
            if (data > (*T)->rchild->data)
            {
                rrRotation(*T, T);
            }
            else
            {
                llRotation((*T)->rchild, &((*T)->rchild));
                rrRotation(*T, T);
            }
        }
    }
    (*T)->height = 1+max(getHeight((*T)->lchild),getHeight((*T)->rchild));
}

void preOrder(TreeNode *T)
{
    if (T)
    {
        printf("%d %d %d\n", T->data,getHeight(T->lchild),getHeight(T->rchild));
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}

void inOrder(TreeNode *T)
{
    if (T)
    {
        inOrder(T->lchild);
        printf("%d ", T->data);
        inOrder(T->rchild);
    }
}

int main()
{
    TreeNode *T = NULL;
    int nums[5] = {1, 8, 6, 7, 10};  //建立二叉排序树时不允许有两个相同的
    for (int i = 0; i < 5; i++)
    {
        avlInsert(&T, nums[i]);
    }
    preOrder(T);
    inOrder(T);
    return 0;
}