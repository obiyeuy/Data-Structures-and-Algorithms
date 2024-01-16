#include "stdio.h"
#include <iostream>
using namespace std;
#include "bitree.h"
Status CreateBiTree(BiTree &T) {
	TElemType ch;
    //scanf(&ch);//����ch
	cin>>ch;
    if (ch=='^') T = NULL;//�μ����ÿո��ʾ�գ�������^��ʾ��
    else {
      if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))
        exit(OVERFLOW);
      T->data = ch;              // ���ɸ����
      CreateBiTree(T->lchild);   // ����������
      CreateBiTree(T->rchild);   // ����������
    }
    return OK;  
} // CreateBiTree ���ַ�������ʽ  �� ������ ������   ����һ�ö�����,������^��ʾ

void PreOrder (BiTree T,void( *visit)(TElemType& e))
{ // ������������� 
   if (T) {
      visit(T->data);            // ���ʽ��
      PreOrder(T->lchild, visit); // ����������
      PreOrder(T->rchild, visit);// ����������
   }
}
void InOrder (BiTree T,void( *visit)(TElemType& e))
{ // ������������� 
   if (T) {
      InOrder(T->lchild, visit); // ����������
      visit(T->data);            // ���ʽ��
      InOrder(T->rchild, visit);// ����������
   }
}
void PostOrder (BiTree T,void( *visit)(TElemType& e))
{ // ������������� 
   if (T) {
      PostOrder(T->lchild, visit); // ���������� 
      PostOrder(T->rchild, visit);// ����������      
	  visit(T->data);  // ���ʽ��
   }
}
void visit(TElemType& e){//���ʺ���
	cout<<e;
}

//BiTNode *GoFarLeft(BiTree T, Stack *S){//ԭ�μ��еĺ���ͷ����Ϊ�����  &S
BiTNode *GoFarLeft(BiTree T, Stack &S){//�ҵ���T�������½��
   if (!T )  return NULL;
   while (T->lchild ){
      Push(S, T);
      T = T->lchild;
   }
   return T;
}

void InOrder_I(BiTree T, void (*visit)(TElemType& e)){
   //Stack *S;
   Stack S ;
   InitStack(S);//��ʼ��ջS
   BiTree t = GoFarLeft(T, S);  // �ҵ������µĽ��
   while(t){
      visit(t->data);
      if (t->rchild)
         t = GoFarLeft(t->rchild, S);
     else if ( !StackEmpty(S ))    // ջ����ʱ��ջ
         //t = Pop(S);
		 Pop(S,t);
         else    t = NULL; // ջ�ձ�����������
    } // while
}// Inorder_I           
void CountLeaf (BiTree T,  int& count){//ͳ��Ҷ�ӽڵ�ĸ���
   if ( T ) {
      if ((!T->lchild)&& (!T->rchild))
         count++;     // ��Ҷ�ӽ�����
      CountLeaf( T->lchild, count);  
      CountLeaf( T->rchild, count); 
   } // if
} // CountLeaf
int Depth (BiTree T ){ // ���ض����������
   int  depthval,depthLeft,depthRight;
   if ( !T )    depthval = 0;
   else   {
     depthLeft = Depth( T->lchild );
     depthRight= Depth( T->rchild );
     depthval = 1 + (depthLeft>depthRight?depthLeft : depthRight);
   } 
   return depthval;
}

