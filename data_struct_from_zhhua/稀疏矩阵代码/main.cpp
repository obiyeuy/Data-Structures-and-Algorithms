#include <iostream>
#include   <stdlib.h>
#include   <time.h>
using namespace std;
#define  MAXSIZE  12500
#define OK 1
typedef int Status;
typedef int ElemType;
typedef struct
{
    int  i, j;       //该非零元的行下标和列下标
    ElemType  e;    // 该非零元的值
} Triple;            // 三元组类型
typedef struct
{
    Triple  data[MAXSIZE + 1];    //data[0]未用
    int     mu, nu, tu; //行数、列数、总数
} TSMatrix;               // 稀疏矩阵类型

/*****************************************************************
CreatMatrix(TSMatrix &M)随机生成一个稀疏因子为fact的row*col的矩阵
    fact∈[0,0.05]
    row∈[1,100]
    col∈[1,100]
*******************************************************************/
Status CreatMatrix(TSMatrix &M)
{
    int row, col; //行数，列数
    float fact;//稀疏因子
    srand(time(NULL));
    row = rand() % 100 + 1; //生成行数
    col = rand() % 100 + 1; //生成列数
    fact = rand() * 0.05 / RAND_MAX; //生成随机因子
    M.mu = row;
    M.nu = col;
    M.tu = row * col * fact;
    for(int k = 1; k <= M.tu; k++)
    {
        int q = 1;
        do
        {
            M.data[k].i = rand() % row + 1; //生成一个元素的行号
            M.data[k].j = rand() % col + 1; //生成一个元素的列号
            //上面的随机过程有可能重复，应该去重
            if(M.data[k].i == M.data[q].i && M.data[k].j == M.data[q].j)//有重复
            {
                q = 1;
                continue;//转到开始重新生成,重新比对
            }
            q++;
        }
        while(q < k);
        M.data[k].e = rand(); //生成该元素值
    }
    return OK;
}
/**
转置
**/
Status TransposeSMatrix(TSMatrix M, TSMatrix &T)
{
    int p, q, col;
    T.mu = M.nu;
    T.nu = M.mu;
    T.tu = M.tu;
    if (T.tu)
    {
        q = 1;
        for (col = 1; col <= M.nu; ++col)
            for (p = 1; p <= M.tu; ++p)
                if (M.data[p].j == col)
                {
                    T.data[q].i = M.data[p].j;
                    T.data[q].j = M.data[p].i;
                    T.data[q].e = M.data[p].e;
                    ++q;
                }
    }
    return OK;
}
/**
输出
**/
void outputMatrix(TSMatrix M)
{
    cout << "--------------------------------------------" << endl;
    cout << M.mu << "*" << M.nu << "  total = " << M.tu << endl;
    cout << "--------------------------------------------" << endl;
    for(int i = 1; i <= M.tu; i++)
    {
        cout << "(" << M.data[i].i << "," << M.data[i].j << "," << M.data[i].e << ")" << endl;
    }
}

int main()
{
    TSMatrix M, T;
    CreatMatrix(M);
    outputMatrix(M);
    TransposeSMatrix( M, T);
    outputMatrix(T);
    return 0;
}
