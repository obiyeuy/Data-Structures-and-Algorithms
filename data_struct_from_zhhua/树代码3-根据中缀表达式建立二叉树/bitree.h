#include "stack_op.h"
#include "stack.h"
#include <iostream>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;

/*typedef char TElemType;
typedef struct BiTNode { // ���ṹ
    TElemType      data;
    struct BiTNode  *lchild, *rchild; // ���Һ���ָ��                                  
} BiTNode, *BiTree; */ //��㼰���Ķ�����stack.h��
void CrtExptree(BiTree &T, char exp[] );//�Ա��ʽ�ַ�������ʽ����һ�ű��ʽ������,(a+b)*c-d/e
void PreOrder (BiTree T,void( *visit)(TElemType& e));//�ȸ�����
void InOrder (BiTree T,void( *visit)(TElemType& e));//�и�����
void PostOrder (BiTree T,void( *visit)(TElemType& e));//�������
void visit(TElemType& e);//���ʺ���
void CrtNode(BiTree& T,char ch);//����Ҷ�ӽڵ�
void CrtSubtree (BiTree& T, char c);//��������
Status IN(char ch,char OP[]);//��ch�Ƿ�����OP������Ƿ���TRUE�����򷵻�ERROR
Status precede(char c,char ch);//�Ƚ������c��ch�����ȼ�,c����ch����true�����򷵻�FALSE
