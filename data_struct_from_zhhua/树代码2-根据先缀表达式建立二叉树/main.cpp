#include "bitree.h"
#include <iostream>
using namespace std;
int  main(){
	BiTree bt;//�����������bt
	cout<<"����������һ���������ַ�������ʽ������ʽ  -��+ a b c / d e"<<endl;
	CreateBiTree(bt);//������  ���ַ�������ʽ������ʽ  -��+ a b c / d e
	cout<<"�������"<<endl;
	PreOrder(bt,visit);//�������
	cout<<"\n�������"<<endl;
	InOrder(bt,visit);//�ݹ��������
	cout<<"\n�������"<<endl;
	PostOrder(bt,visit);//�������
	cout<<endl;
	return 0;
}