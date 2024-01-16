#include <stdlib.h>
#include <stdio.h>

// 树的节点赋值，这个值成为权值
// 哈夫曼树是所有叶子节点的带权路径长度之和最小
// 哈夫曼编码

// 使用指定权值的节点列表生成哈夫曼树
// 遍历哈夫曼树
// 取节点序列中第一小和第二小的节点
// 树的存储结构(建议使用顺序存储)

typedef struct TreeNode
{
    int weight;
    int parent;
    int lchild;
    int rchild;
} TreeNode;

typedef struct HFTree
{
    TreeNode *data;
    int length;
} HFTree;

HFTree *initTree(int *weight, int length)
{
    HFTree *T = (HFTree *)malloc(sizeof(HFTree));
    T->data = (TreeNode *)malloc(sizeof(TreeNode) * (2 * length - 1));
    T->length = length;
    for (int i = 0; i < length; i++)
    {
        T->data[i].weight = weight[i];
        T->data[i].parent = 0;
        T->data[i].lchild = -1;
        T->data[i].rchild = -1; //-1???
    }
    return T;
}

int *selectMin(HFTree *T)
{
    int min = 10000;
    int secondMin = 10000;
    int minIndex;
    int secondIndex;
    for (int i = 0; i < T->length; i++)
    {
        if (T->data[i].parent == 0)
        {
            if (T->data[i].weight < min)
            {
                min = T->data[i].weight;
                minIndex = i;
            }
        }
    }
    for (int i = 0; i < T->length; i++)
    {
        if (T->data[i].parent == 0 && i != minIndex)
        {
            if (T->data[i].weight < secondMin)
            {
                secondMin = T->data[i].weight;
                secondIndex = i;
            }
        }
    }
    int *res = (int *)malloc(sizeof(int) * 2);
    res[0] = minIndex;
    res[1] = secondIndex;
    return res;
}

void createHFTree(HFTree *T)
{
    int *res;
    int minIndex;
    int secondMinIndex;
    int length = T->length * 2 - 1;
    for (int i = T->length; i < length; i++)
    {
        res = selectMin(T);
        minIndex = res[0];
        secondMinIndex = res[1];
        T->data[i].weight = T->data[minIndex].weight + T->data[secondMinIndex].weight;
        T->data[i].lchild = minIndex;
        T->data[i].rchild = secondMinIndex;
        T->data[minIndex].parent = i;
        T->data[secondMinIndex].parent = i;
        T->length++;
    }
}

void preOrder(HFTree *T, int index)
{
    if (index != -1)
    {
        printf("%d ", T->data[index].weight);
        preOrder(T, T->data[index].lchild);
        preOrder(T, T->data[index].rchild);
    }
}

int main()
{
    // int weight[4] = {1, 2, 3, 4};
    // HFTree *T = initTree(weight, 4);
    int weight[7] = {5,1,3,6,11,2,4};
    HFTree *T = initTree(weight, 7);
    int *res = selectMin(T);
    printf("%d %d\n", res[0], res[1]);
    createHFTree(T);
    preOrder(T, T->length - 1);
    return 0;
}