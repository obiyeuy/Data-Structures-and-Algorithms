#include "bitree.h"
#include <iostream>
using namespace std;
int  main(){
	BiTree bt;//�����������bt
	cout<<"����������һ�������������������^��ʾ����AB^C^^D^^"<<endl;
	CreateBiTree(bt);//������  AB^C^^D^^
	cout<<"�������"<<endl;
	PreOrder(bt,visit);//�������
	cout<<"\n�ݹ��������"<<endl;
	InOrder(bt,visit);//�ݹ��������
	cout<<"\n�ǵݹ��������"<<endl;
	InOrder_I(bt,visit);//�ǵݹ��������
	cout<<"\n�������"<<endl;
	PostOrder(bt,visit);//�������
	cout<<"\nҶ�ӽڵ�ĸ���Ϊ��";
	int count=0;
	CountLeaf (bt,count);//ͳ��Ҷ�ӽڵ�ĸ���
	cout<<count<<endl;
	cout<<"�����������Ϊ��"<<Depth (bt);// ���ض����������
    cout<<endl;
	return 0;
}