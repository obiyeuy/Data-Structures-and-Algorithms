#include <stdlib.h>
#include <stdio.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} TreeNode;

// void createTree(TreeNode** T){
//     //创建二叉树
//     char data;
//     scanf("%c",&data);
//     if(data == '#'){
//         *T=NULL;
//     }else{
//         *T = (TreeNode*)malloc(sizeof(TreeNode));
//         (*T)->data = data;
//         createTree(&((*T)->lchild));
//         createTree(&((*T)->rchild));
//     }
// }

void createTree(TreeNode** T,char* data,int* index){
    //创建二叉树
    char ch;
    ch = data[*index];
    *index += 1;
    if(ch == '#'){
        *T=NULL;
    }else{
        *T = (TreeNode*)malloc(sizeof(TreeNode));
        (*T)->data = ch;
        createTree(&((*T)->lchild),data,index);
        createTree(&((*T)->rchild),data,index);
    }
}

// // C++才能使用(书中学的方法)
// void createTree(TreeNode* &T,char* data,int* index){
//     //创建二叉树
//     char ch;
//     ch = data[*index];
//     *index += 1;
//     if(ch == '#'){
//         T=NULL;
//     }else{
//         T = (TreeNode*)malloc(sizeof(TreeNode));
//         T->data = ch;
//         createTree(T->lchild,data,index);
//         createTree(T->rchild,data,index);
//     }
// }


void preOrder(TreeNode* T){
    if(T ==NULL){
        return;
    }else{
        //先办事
        printf("%c ",T->data);
        //再处理左孩子与右孩子
        preOrder(T->lchild);
        preOrder(T->rchild);
    }
}

void copy(TreeNode* T,TreeNode* & newT){
    if(T==NULL){
        newT = NULL;
        return;
    }else{
        newT = (TreeNode*)malloc(sizeof(TreeNode));
        newT->data = T->data;
        copy(T->lchild,newT->lchild);
        copy(T->rchild,newT->rchild);
    }
}

int main(){
    TreeNode* T;
    TreeNode* newT;
    // char data[] = "AB##C##";
    char data[] = "ABD##E##CF##G##";
    int index = 0;
    // createTree(&T);
    createTree(&T,data,&index);
    // createTree(T,data,&index);
    preOrder(T);
    printf("\n");
    copy(T,newT);
    preOrder(newT);
    return 0;
}
