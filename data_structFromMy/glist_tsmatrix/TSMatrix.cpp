#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAXSIZE 12500

typedef int Elemtype;

typedef struct {
	int i, j;
	Elemtype e;
}Triple;

typedef struct {
	Triple data[MAXSIZE + 1];  //data[0]不用
	int mu, nu, tu;   //矩阵的行数、列数和非零元素个数
}TSMatrix;


TSMatrix  M;

bool TransposeSMatrix(TSMatrix M, TSMatrix& T) {
	int p, q, col;
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	if (T.tu) {
		q = 1;
		for (col = 1; col <= M.nu;++col) {
			for (p = 1; p <= M.tu; ++p) {
				T.data[q].i = M.data[p].j;
				T.data[q].j = M.data[p].i;
				T.data[q].e = M.data[p].e;
				++q;
			}
		}
	}
	return true;
}    //时间复杂度是O(M.nu*M.tu)




