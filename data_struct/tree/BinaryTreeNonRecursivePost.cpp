#include <stdlib.h>
#include <stdio.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    int flag;
} TreeNode;

typedef struct StackNode
{
    TreeNode *data;
    struct StackNode *next;
} StackNode;

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
        (*T)->flag = 0;
        createTree(&((*T)->lchild), data, index);
        createTree(&((*T)->rchild), data, index);
    }
}

StackNode *initStack()
{
    StackNode *S = (StackNode *)malloc(sizeof(StackNode));
    S->data = NULL;
    S->next = NULL;
    return S;
}

void push(TreeNode *data, StackNode *S)
{
    StackNode *node = (StackNode *)malloc(sizeof(StackNode));
    node->data = data;
    node->next = S->next;
    S->next = node;
}

int isEmpty(StackNode *S)
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

StackNode *pop(StackNode *S)
{
    if (isEmpty(S))
    {
        return NULL;
    }
    else
    {
        StackNode *node = S->next;
        S->next = node->next;
        return node;
    }
}

StackNode *getTop(StackNode *S)
{
    if (isEmpty(S))
    {
        return NULL;
    }
    else
    {
        return S->next;
    }
}

// 方法一：将已经访问过的做上标记
void postOrder(TreeNode* T){
    TreeNode* node = T;
    StackNode* S = initStack();
    while(node || !isEmpty(S)){
        if(node){
            push(node,S);
            node = node->lchild;
        }else{
            TreeNode* top = getTop(S)->data;
            if(top->rchild && top->rchild->flag==0){
                top = top->rchild;
                push(top,S);
                node = top->lchild;
            }else{
                top = pop(S)->data;
                printf("%c ",top->data);
                top->flag = 1;
            }
        }
    }
}


// 方法二：用两个栈实现
// 后序遍历，先序遍历是中左右，后序遍历是左右中
// 那么我们只需要调整一下先序遍历的代码顺序，就变成中右左的遍历顺序
// 即将先序遍历改为中右左，把访问改为压栈
// 然后再出栈，输出的结果顺序就是左右中了
void myPostOrder(TreeNode* T){
    TreeNode* node = T;
    StackNode* S = initStack();
    StackNode* reverse = initStack();
    while(node || !isEmpty(S)){
        if(node){
            push(node,reverse);
            push(node,S);
            node = node->rchild;
        }else{
            node = pop(S)->data;
            node = node->lchild;
        }
    }
    while(!isEmpty(reverse)){
        printf("%c ",pop(reverse)->data->data);
    }
}


int main()
{
    TreeNode *T;
    // char data[] = "AB##C##";
    char data[] = "ABD##E##CF##G##";
    int index = 0;
    createTree(&T, data, &index);
    postOrder(T);
    printf("\n");
    myPostOrder(T);
    return 0;
}