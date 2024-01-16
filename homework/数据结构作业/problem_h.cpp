#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include<vector>

typedef struct BiTNode {
	char s;
	struct BiTNode* lchild;
	struct BiTNode* rchild;
}BiTNode,*BiTree;

// 比较两个运算符的优先级
// -1:s1<s2  0:s1==s2  1:s1>s2
int compare(char s1, char s2) {
	
	if ((s1 == '+' || s1 == '-') && (s2 == '*' || s2 == '/')) {
		return -1;
	}
	if (((s1 == '+' || s1 == '-') && (s2 == '+' || s2 == '-')) ||((s1 == '*' || s1 == '/') && (s2 == '*' || s2 == '/'))) {
		return 0;
	}
	if ((s1 == '*' || s1 == '/') && (s2 == '+' || s2 == '-')) {
		return 1;
	}
}


bool isFour(char s) {
	return (s == '+') || (s == '-') || (s == '*') || (s == '/');
}


BiTree createTree(string data, int start, int end) {
	// 去掉最外侧括号
	if (data[start] == '(' && data[end] == ')') {
		start++; end--;
	}

	BiTree T = new BiTNode;
	int size = end - start + 1;

	if (size <= 0) {
		return NULL;
	}
	// 长度为1, 数字直接作为叶结点
	else if (size == 1) {
		T->s = data[start];
		T->lchild = T->rchild = NULL;
		return T;
	}
	else {
		char chosen = { 0 };   // 记录选中的运算符
		int lcount = 0;
		int mid = 0;  // lcount记录左括号数量，mid记录选中运算符位置
		for (int i = start; i <= end; i++) {
			if (data[i] == '(') lcount++;  // 这两行用于记录括号匹配是否结束
			if (data[i] == ')') lcount--;
			// isFour()用于判断是否是四则运算符, lcount==0表示外层不存在括号, 
			// compare()用于比较两运算符优先级 
			if (isFour(data[i]) && lcount == 0 && compare(chosen, data[i]) != -1) {
				chosen = data[i];  
				mid = i;
			}
		}
		T->s = chosen;
		// 对左右子树分别赋值，递归调用此函数 
		T->lchild = createTree(data, start, mid - 1);
		T->rchild = createTree(data, mid + 1, end);
		return T;
	}
}

void preTraverse(BiTree T)
{
	if (T == NULL)return;
	else
	{
		cout << T->s;
		preTraverse(T->lchild);
		preTraverse(T->rchild);
	}
}
void midTraverse(BiTree T)
{
	if (T == NULL)return;
	else
	{
		midTraverse(T->lchild);
		cout << T->s;
		midTraverse(T->rchild);
	}
}
void postTraverse(BiTree T)
{
	if (T == NULL)return;
	else
	{
		postTraverse(T->lchild);
		postTraverse(T->rchild);
		cout << T->s;
	}
}


int main() {

	string vec;
	
	cin >> vec;
	int length = 0;
	while (vec[length] != '\0') {
		length++;
	}
	BiTree r;
	r = createTree(vec,0,length-1);//构建二叉树并且存入二叉树指针r中 
	preTraverse(r);
	cout << endl;
	midTraverse(r);
	cout << endl;
	postTraverse(r);
	return 0;
}

