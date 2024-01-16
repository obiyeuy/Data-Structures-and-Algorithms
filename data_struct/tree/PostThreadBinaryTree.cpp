#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    struct TreeNode* parent;
    int ltag;
    int rtag;
} TreeNode;

void createTree(TreeNode **T, char *data, int *index,TreeNode* parent)
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
        (*T)->parent = parent;
        createTree(&((*T)->lchild), data, index,*T);
        createTree(&((*T)->rchild), data, index,*T);
    }
}

void PreThreadBinaryTree(TreeNode *T, TreeNode **pre)
{
    if (T)
    {
        PreThreadBinaryTree(T->lchild, pre);
        PreThreadBinaryTree(T->rchild, pre);
        if (T->lchild == NULL)
        {
            T->ltag = 1;
            T->lchild = *pre;
        }
        if (*pre != NULL && (*pre)->rchild == NULL)
        {
            (*pre)->rtag = 1;
            (*pre)->rchild = T;
        }
        *pre = T;
    }
}

TreeNode *getFirst(TreeNode *T)
{
    while(T->ltag == 0){
        T = T->lchild;
    }
    if(T->rtag == 0){
        return getFirst(T->rchild);
    }
    return T;
}
TreeNode* getNext(TreeNode* node){
    if(node->rtag ==1){
        return node->rchild;
    }else{
        //如果是根节点
        if(node->parent==NULL){
            return NULL;
        //如果是右孩子
        }else if(node->parent->rchild ==node){
            return node->parent;
        }
        //如果是左孩子
        else{
            if(node->parent->ltag ==0){   //???????
                return getFirst(node->parent->rchild);
            }else{
                return node->parent;
            }
        }
    }
}

int main()
{
    TreeNode *T;
    TreeNode *pre = NULL;
    // char data[] = "AB##C##";
    char data[] = "ABD##E##CF##G##";
    int index = 0;
    createTree(&T, data, &index,NULL);
    PreThreadBinaryTree(T, &pre);
    for (TreeNode *node = getFirst(T); node != NULL; node = getNext(node))
    {
        printf("%c ", node->data); 
    }// D E B F G C A
    return 0;
}