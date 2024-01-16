#include<bits/stdc++.h>
#include<stdlib.h>
#include<iostream>
#include<stack>
using namespace std;

typedef struct Node
{
    char data;
    struct Node* lchild;
    struct Node* rchild;
} TreeNode, * Tree;

int ans;

void createtree(Tree& T)//引用
{
    char c;
    cin >> c;
    if (c == '#')
    {
        T = NULL;
    }
    else
    {
        T = new TreeNode;//建根节点
        T->data = c;
        createtree(T->lchild);//建左子树
        createtree(T->rchild);//建右子树
        if (T->lchild == NULL && T->rchild == NULL)ans++;
    }
}

void preTraverse(Tree T)
{
    if (T == NULL)return;
    else
    {
        cout << T->data;
        preTraverse(T->lchild);
        preTraverse(T->rchild);
    }
}
void midTraverse(Tree T)
{
    if (T == NULL)return;
    else
    {
        midTraverse(T->lchild);
        cout << T->data;
        midTraverse(T->rchild);
    }
}
void postTraverse(Tree T)
{
    if (T == NULL)return;
    else
    {
        postTraverse(T->lchild);
        postTraverse(T->rchild);
        cout << T->data;
    }
}


int Depth(TreeNode* T)
{
    int m, n;
    if (T == NULL)
        return 0; //如果是空树，深度为0，递归结束
    else
    {
        m = Depth(T->lchild); //递归计算左子树的深度记为m
        n = Depth(T->rchild); //递归计算右子树的深度记为n
        if (m > n)
            return (m + 1); //二叉树的深度为m 与n的较大者加1
        else
            return (n + 1);
    }
}



void InorderTraversal(TreeNode* T)
{
    TreeNode* stack[100], * p = T;
    int top = 0;
    if (T == NULL)
    {
        return;
    }
    while (p != NULL || top > 0)
    {
        if (p != NULL)//遇到非空结点即压栈，之后一路向左 
        {
            stack[top++] = p;
            p = p->lchild;
        }
        else//遇到空节点则弹栈，访问，向右一步走 
        {
            p = stack[--top];
            printf("%c", p->data);
            p = p->rchild;
        }
    }
}


int main(void) {
    Tree root;
    createtree(root);
    if (root)
    {
        preTraverse(root);
        cout << endl;
        midTraverse(root);
        cout << endl;
        postTraverse(root);
        cout << endl;
        cout << ans << endl;
        cout << Depth(root) <<endl;
        InorderTraversal(root);
        cout << endl;
    }
    else//只输入了一个'#'
        cout << ans<< endl;
    return 0;
}
