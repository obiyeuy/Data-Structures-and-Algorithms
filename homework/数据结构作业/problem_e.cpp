#include<stdlib.h>
#include<stdio.h>

#define _CRT_SECURE_NO_WARNINGS
#define MAX_INIT_SIZE 50



typedef struct {
	int datas[3*MAX_INIT_SIZE];
	int rows, cols, nums;
}zong;


void Insert(zong* B, int i, int j, int x, int k) {
	B->datas[3*k] = i;
	B->datas[3*k+1] = j;
	B->datas[3*k+2] = x;
}

void Trans(zong M, zong* T) {
	T->cols = M.rows;
	T->rows = M.cols;
	T->nums = M.nums;
	if (T->nums) {
		int q = 0;
		for (int i = 1; i <= M.cols; i++) {
			for (int p = 0; p < M.nums; p++) {
				if (M.datas[3*p+1] == i) {
					T->datas[3*q+1]= M.datas[3*p];
					T->datas[3*q] = M.datas[3*p+1];
					T->datas[3*q+2] = M.datas[3*p+2];
					q++;
				}
			}
		}
	}
}

int main(void) {
	int row1, col1, num1;
	scanf("%d%d%d", &row1, &col1, &num1);
	zong M;

	M.cols = col1;
	M.rows = row1;
	M.nums = num1;
	for (int n = 0; n < num1; n++) {
		int i, j, data;
		scanf("%d%d%d", &i, &j, &data);
		Insert(&M, i, j, data, n);
	}
	zong T;

	T.cols = row1;
	T.rows = col1;
	T.nums = num1;
	Trans(M, &T);
	printf("%d %d %d\n", T.rows, T.cols, T.nums);
	for (int i = 0; i < num1; i++) {
		printf("%d %d %d\n", T.datas[3*i], T.datas[3*i+1], T.datas[3*i+2]);
	}
}
