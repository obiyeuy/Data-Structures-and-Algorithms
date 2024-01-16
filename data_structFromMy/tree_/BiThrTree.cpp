#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef char TElemType;
typedef enum{Link,Thread} PointerThr;
// Link==0:指针，Thread==1:线索

typedef struct BiThrNode{
    TElemType data;
    struct BiThrNode* lchild;
    struct BiThrNode* rchild;
    PointerThr LTag,RTag;
}BiThrNode,*BiThrTree;


void InOrderThreading(BiThrTree tree,BiThrNode* &p){
    if(tree){  // 对以tree为根的非空二叉树进行线索化
        InOrderThreading(tree->lchild,p);   // 左子树线索化
        if(!tree->lchild){  // 建前驱线索
            tree->LTag = Thread;
            tree->lchild = p;
        }
        if(!p->rchild){  // 建后继线索
            p->RTag = Thread;
            p->rchild = tree;
        }
        p = tree;  // 保持 pre 指向 p 的前驱
        InOrderThreading(tree->rchild,p); // 右子树线索化
    }
}


// bool InOrderThreading(BiThrTree &Thrt,BiThrTree T){
//     if(!(Thrt = (BiThrTree)malloc(sizeof(BiThrNode)))){
//         return false;
//     }
//     T->LTag = Link;
//     T->RTag = Thread;
//     T->rchild = Thrt;
//     if(!T){
//         Thrt->lchild = Thrt;
//     }else{
//         Thrt->lchild = T;

//     }
    
// }

//线索链表的遍历算法
// 由于在线索链表中添加了遍历中得到的“前驱”和“后继”的信息，省去了栈（递归栈或非递归栈），
// 因为前后关系已经通过存储结构解决。从而简化了遍历的算法

//对中序线索化链表的遍历算法
void InOrderTraverse_Thr(BiThrTree T){
    BiThrNode* p = T->lchild;   //p指向根节点
    while(p!=T){   //空树或遍历结束时，p==T
        while(p->LTag == Link){  //第一个节点
            p = p->lchild;
            printf("%c",p->data);  //访问
        }
        while(p->RTag == Thread && p->rchild != T){
            p = p->rchild;
            printf("%c",p->data); //访问后继节点
        }
        p = p->rchild;  //p进其右子树根
    }
}