#include "bitree.h"
#include <iostream>
#define MAXNUM 100
using namespace std;
int  main(){
	BiTree T;
	char exp[MAXNUM];
	cout<<"input an expression ended by # such as '(a+b)*c-d/e#':"<<endl;
	cin>>exp;
	CrtExptree(T,exp);
	cout<<"sucess and the PreOrder is:"<<endl;
	PreOrder(T,visit);
	cout<<"\nthe PostOrder is:"<<endl;
	PostOrder(T,visit);
	cout<<endl;
	return 0;
}