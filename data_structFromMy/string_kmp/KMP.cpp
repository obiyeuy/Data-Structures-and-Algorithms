#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXSTRLEN 256


//定长顺序存储表示
typedef unsigned char SString[MAXSTRLEN + 1];
//SString ss;


//堆分配存储表示
typedef struct {
	char* ch; //若是非空串，则按串长分配存储区    否则ch为NULL
	int length;
}HString;


//串的块链存储表示
#define CHUNKSIZE 80
typedef struct Chunk {  //结点结构
	char ch[CHUNKSIZE];
	struct Chunk* next;
}Chunk;

typedef struct {     //串的链表结构
	Chunk *head, * tail;   //串的头和尾指针
	int curlen;       //串的当前长度
}LString;


//模式匹配简单算法
int Index(SString S, SString T, int pos) {
	int i = pos;
	int j = 1;
	while (i <= S[0] && j <= T[0]) {
		if (S[i] == T[j]) {   //继续比较后续字符
			++i;
			++j;
		}
		else {    //指针回退重新开始匹配
			i = i - j + 2;
			j = 1;
		}
	}
	if (j > T[0]) {
		return i - T[0];
	}
	else {
		return 0;
	}
}  //最好的时间复杂度是O(n+m)，最差的是O(n*m)


//KMP算法
//主串指针不回溯，模式串向后滑动至某个位置上    kmp算法可以达到O(n+m)
void get_next(SString S, int next[]) {
	int j = 1, k = 0;
	next[1] = 0;
	while (j < S[0]) {
		if (k == 0 || S[j] == S[k]) {
			++j;
			++k;
			next[j] = k;    // next[++j] = ++k;
		}
		else {
			k = next[k];    //T[j] != T[k]时,k跳转到next[k]
		}
	}
}

int Index_KMP(SString S, SString T, int pos) {
	int i = pos;
	int j = 1;
	int next[MAXSTRLEN];
	get_next(T,next);
	while (i <= S[0] && j <= T[0]) {
		if (j == 0 || S[i] == T[j]) {
			++i;
			++j;
		}
		else {
			j = next[j];  // i不变，j后退
		}
		if (j > T[0]) {    //匹配成功
			return i - T[0];
		}
		else {  // 返回不匹配标志
			return 0; 
		}
	}
}



