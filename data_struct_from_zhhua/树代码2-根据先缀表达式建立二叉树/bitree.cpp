#include "stdio.h"
#include <iostream>
using namespace std;
#include "bitree.h"
Status CreateBiTree(BiTree &T) {
	TElemType ch;
    //scanf(&ch);//����ch
	cin>>ch;
	if ((ch<='z'&&ch>='a')||(ch<='Z'&&ch>='A')) {
      if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))
        exit(OVERFLOW);
      T->data = ch;              // ���ɸ����
      T->lchild = NULL;   // ����������
      T->rchild = NULL;   // ����������	
	}
    else {
      if (!(T = (BiTNode *)malloc(sizeof(BiTNode))))
        exit(OVERFLOW);
      T->data = ch;              // ���ɸ����
      CreateBiTree(T->lchild);   // ����������
      CreateBiTree(T->rchild);   // ����������
    }
    return OK;  
} // CreateBiTree ���ַ�������ʽ������ʽ  -��+ a b c / d e

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



