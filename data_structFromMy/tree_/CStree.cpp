#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stack>
#include<queue>
using namespace std;

#define MAX_TREE_SIZE 100;

typedef char TElemType;

typedef struct CSNode{
    TElemType data;
    struct CSNode *firstchild,*nextsibling;
}CSNode,*CSTree;

//建树的存储结构的算法
// 假设以二元组(F,C)的形式自上而下、自左而右依次输入树的各边，建立树的孩子-兄弟链表。
void CreatTree(CSTree &T){
    char fa,ch;
    scanf("%c,%c",&fa,&ch);
    while(ch!='#'){
        CSNode* r;
        CSNode* p;
        p->data = ch;  //创建节点
        p->firstchild = NULL;
        p->nextsibling = NULL;
        queue<CSTree> Q;  //指针入队列
        Q.push(p);
        if(fa == '#'){  //所建为根节点
            T = p; 
        }else{  //非根节点的情况
            CSNode* s = Q.front();
            while(s->data!=fa){
                Q.pop();
                s = Q.front();
            }
            if(!(s->firstchild)){
                s->firstchild = p;
                r = p;
            }else{
                r->nextsibling = p;
                r = p;
            }
        }
        getchar();
        scanf("%c,%c",&fa,&ch);
    }
}

//树的遍历
//先根遍历：
//若树不空，则先访问根节点，然后依次先根遍历各棵子树


// 后根(次序)遍历:
// 若树不空，则先依次后根遍历各棵子树，然后访问根结点


// 按层次遍历:
// 若树不空，则自上而下自左至右访问树中每个结点


//求树的深度的算法
int TreeDepth(CSTree T){
    if(!T){
        return 0;
    }else{
        int h1 = TreeDepth(T->firstchild);
        int h2= TreeDepth(T->nextsibling);
        return max(h1+1,h2);
    }
}


//输出树中所有根到叶子的路径的算法
void AllPath(CSTree T,stack<TElemType> &S){
    if(T){
        S.push(T->data);
        if(T->firstchild !=NULL && T->nextsibling !=NULL){
            printf("%c",S.top());
        }
        else{
            AllPath(T->firstchild,S);
            AllPath(T->nextsibling,S);
        }
        S.pop();
    }
}

void OutPath(CSTree T,stack<TElemType>&S){
    while(!T){
        S.push(T->data);
        if(!T->firstchild){
            printf("%c",S.top());
        }else{
            OutPath(T->firstchild,S);
        }
        S.pop();
        T = T->nextsibling;
    }
}

int main(){
    CSTree T;
    CreatTree(T);
    printf("%d",TreeDepth(T));
}