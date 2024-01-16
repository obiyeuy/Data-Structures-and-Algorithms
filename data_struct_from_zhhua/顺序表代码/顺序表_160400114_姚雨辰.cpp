
//代码主要按照自己的思路，功能和结构参照ppt
//欢迎bug反馈
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
//宏定义四个值
#define YES 1
#define NO  0
#define Init_Size 100//初始化空间
#define Add_Size 20//每次增加的空间

typedef int element;//默认线性表元素

typedef struct {//线性表结构体
	element* info;
	int length;
	int size;
} List;


int compare(element a, element b)//酱油函数
{
	if (a > b)
		return YES;
	else
		return NO;
}
int find_function_item(List &L,element k,int (*func)(element a,element b))//函数指针，刚刚百度使用
{
	int i;
	for (i = 0; i < L.length; i++)
	{
		if ((*func)(L.info[i], k))
		{
			return i + 1;
		}
	}
	return NO;
}

void show_all_elements(List &L)//打印线性表
{
	int i;
	for (i = 0; i < L.length; i++)
	{
		printf("%d ", L.info[i]);
	}
	printf("\n");
}
int InitList(List &L)//初始化线性表
{
	L.info = (element*)malloc(sizeof(element)*Init_Size);
	if (!L.info)
	{
		return NO;
	}
	L.size = Init_Size;
	L.length = 0;
	return YES;
}
int addroom(List &L)//分配空间
{
	element* temp;
	temp = (element*)realloc(L.info,sizeof(element)*(L.length+ Add_Size));
	if (!temp)
	{
		return NO;
	}
	L.info = temp;
	L.size += Add_Size;
	return YES;
}

int append_element(element e, List &L)//在线性表末尾添加新元素
{
	if (L.length >= L.size)
	{
		return NO;
	}
	L.info[L.length] = e;
	L.length++;
	return YES;
}


int insert_element(element e, int loc, List &L)//插入某个元素到第loc个元素的位置
{
	if (loc > L.length + 1 || loc<1 || L.length >= L.size)
	{
		return NO;
	}
	if (loc == L.length + 1)
	{
		return append_element(e, L);
	}
	int i;
	for (i = L.length - 1; i >= loc - 1; i--)
	{
		L.info[i + 1] = L.info[i];
	}
	L.info[loc - 1] = e;
	L.length++;
	return YES;
}

int locate_element(element e, List &L)//返回 值为e的第一个元素是线性表的第几个元素
{
	int i = 0;
	for (i = 0; i < L.length; i++)
	{
		if (L.info[i] == e)
			return i + 1;
	}
	return NO;
}

int delete_element(element e, List &L)//删除所有值为e的元素
{
	int p1 = 0, p2 = 0;
	int i = 0;
	for (i = 0; i < L.length; i++)
	{
		L.info[p2] = L.info[p1++];
		if (L.info[i] != e)
			p2++;
	}
	L.length -= p1 - p2;
	return YES;
}
int main()
{//测试程序
	List test_L;
	InitList(test_L);
	printf("length=%d,size=%d\n", test_L.length, test_L.size);


	append_element(6,test_L);
	append_element(7,test_L);
	int i;
	for (i = 0; i < 4; i++)
	{
		append_element(i, test_L);
	}
	show_all_elements(test_L);


	insert_element(8, 3, test_L);
	show_all_elements(test_L);
	insert_element(8, 6, test_L);
	show_all_elements(test_L);


	delete_element(8, test_L);
	show_all_elements(test_L);

	int m = locate_element(6, test_L);
	printf("%d\n", m);


	addroom(test_L);
	printf("length=%d,size=%d\n", test_L.length, test_L.size);

	int (*cp)(element a, element b);
	cp = &compare;
	int n = find_function_item(test_L, 6, cp);
	printf("n=%d\n", n);

	system("pause");
}