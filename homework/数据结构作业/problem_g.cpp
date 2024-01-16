
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
    c = getchar();
    if (c == '\n')
    {
        T = new TreeNode;
        T->data = c;
        T->lchild = NULL;
        T->rchild = NULL;
        return;
    }
    if ((c <= 'z' && c >= 'a')||(c <= 'Z' && c >= 'A'))
    {
        T = new TreeNode;
        T->data = c;
        T->lchild = NULL;
        T->rchild = NULL;
        ans++;
    }
    else if((c=='-') || (c=='+') || (c=='/') || (c=='*'))
    {
        T = new TreeNode;//建根节点
        T->data = c;
        createtree(T->lchild);//建左子树
        createtree(T->rchild);//建右子树
    }
}

void preTraverse(Tree T)
{
    if (T == NULL)return;
    else
    {
        putchar(T->data);
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
        putchar(T->data);
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
        putchar( T->data);
    }
}


int main(void) {
    Tree root;
    createtree(root);
    if (ans)
    {
        preTraverse(root);
        cout << endl;
        midTraverse(root);
        cout << endl;
        postTraverse(root);
        cout << endl;
    }else{
        printf("\n");
    }
    
    return 0;
}
