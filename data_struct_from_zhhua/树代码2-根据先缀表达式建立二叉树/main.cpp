#include "bitree.h"
#include <iostream>
using namespace std;
int  main(){
	BiTree bt;//定义二叉树树bt
	cout<<"请先序输入一棵树，以字符串的形式输入表达式  -×+ a b c / d e"<<endl;
	CreateBiTree(bt);//先序建树  以字符串的形式输入表达式  -×+ a b c / d e
	cout<<"先序输出"<<endl;
	PreOrder(bt,visit);//先序遍历
	cout<<"\n中序输出"<<endl;
	InOrder(bt,visit);//递归中序遍历
	cout<<"\n后序输出"<<endl;
	PostOrder(bt,visit);//后序遍历
	cout<<endl;
	return 0;
}