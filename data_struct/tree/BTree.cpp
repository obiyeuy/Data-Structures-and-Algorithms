// B树：一颗多路平衡查找树    几阶就是几路         二分查找树就是一颗二阶的多路平衡查找树

// 特点：
// 每个节点关键字的数量x(向上取整(m/2)-1 <= x <= m-1)   m是阶数
// B树的所有叶子节点都在一层
// 父母亲至少有两子女

//插入：
// 插入必须要在叶子节点上  
// 若关键字的数量>=m,就要进行分裂操作  
// 分裂是从中间劈开，中间的关键字插入到当前节点的父亲节点中，然后将左右两部分变成父亲节点的两个孩子  
// 若没有父亲节点，就将中间节点变成其父亲

//删除：
// 删除的关键字在非叶子节点上
// 删除的关键字在叶子节点上
// 叶子结点的个数正好>最小值，直接删除
// 叶子结点的个数正好=最小值，先借，借不到就合并
// 非叶子节点也需要借或合并

// 1.关键字数组
// 2.孩子数组
// 3.关键字个数
// 4.孩子个数
// 5.父亲指针
// 6.树的阶数

#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int level;  //树的阶数
    int keyNum;   //关键字数量
    int childNum;   //孩子数量
    int* keys;     //关键字数组   从索引为1的位置存储   最大长度为level+1
    struct Node** children;    //孩子数组   最大长度为level
    struct Node* parent;   //父亲节点
}Node;

Node* initNode(int level){
    Node* node=  (Node*)malloc(sizeof(Node));
    node->level = level;
    node->keyNum = 0;
    node->childNum = 0;
    node->keys = (int*)malloc(sizeof(int)*(level+1));
    node->children = (Node**)malloc(sizeof(Node*)*level);
    node->parent = NULL;
    int i;
    for(i = 0;i<level;i++){
        node->keys[i] = 0;
        node->children[i] = NULL;
    }
    node->keys[i]  =0;
    return node;
}

// 在结点处寻找合适的插入索引
int findSuitIndex(Node* node,int data){    //找到在关键字数组中的索引
    int index;
    for(index = 1;index<=node->keyNum;index++){
        if(data<node->keys[index]){
            break;
        }
    }
    return index;
}

// 找到合适的叶子结点
Node* findSuitLeafNode(Node* T,int data){   //找到对应的叶子节点(加入时是在叶子到节点中)
    if(T->childNum == 0){
        return T;
    }else{
        int index = findSuitIndex(T,data);   //孩子节点在数组中的位置就是关键字数组相应位置索引-1
        return findSuitLeafNode(T->children[index-1],data);
    }
}

void addData(Node* node,int data,Node** T){
    int index = findSuitIndex(node,data);
    for(int i = node->keyNum;i>=index;i--){  //为插入关键字移位置
        node->keys[i+1] = node->keys[i];
    }
    node->keys[index] = data;
    node->keyNum++;
    //判断是否进行分裂
    if(node->keyNum == node->level){
        //找到分裂位置
        int mid = node->level/2+node->level%2;
        //分裂
        Node* lchild = initNode(node->level);
        Node* rchild = initNode(node->level);
        for(int i = 1;i<mid;i++){
            addData(lchild,node->keys[i],T);
        }
        for(int i = mid+1;i<=node->keyNum;i++){
            addData(rchild,node->keys[i],T);
        }
        for(int i  =0;i<mid;i++){
            lchild->children[i] = node->children[i];
            if(node->children[i] !=NULL){
                node->children[i]->parent = lchild;
                lchild->childNum++;
            }
        }
        int index = 0;
        for(int i = mid;i<node->childNum;i++){
            rchild->children[index++] = node->children[i];
            if(node->children[i]!=NULL){
                node->children[i]->parent = rchild;
                rchild->childNum++;
            }
        }
        //对父亲进行判断
        if(node->parent ==NULL){
            Node* newParent = initNode(node->level);
            addData(newParent,node->keys[mid],T);
            newParent -> children[0] = lchild;
            newParent -> children[1] = rchild;
            newParent -> childNum = 2;
            lchild -> parent = newParent;
            rchild -> parent = newParent;
            *T = newParent;
        }else{
            int index = findSuitIndex(node->parent,node->keys[mid]);
            lchild->parent = node->parent;
            rchild->parent = node->parent;
            node->parent->children[index-1] = lchild;
            if(node->parent->children[index] != NULL){
                for(int i= node->parent->childNum-1;i>=index;i--){
                    node->parent->children[i+1] = node->parent->children[i];
                }
            }
            node->parent->children[index] = rchild;
            node->parent->childNum++;
            addData(node->parent,node->keys[mid],T);
        }
    }
}

void insert(Node** T,int data){
    Node* node = findSuitLeafNode(*T,data);
    addData(node,data,T);
}

void printTree(Node* T){
    if(T !=NULL){
        for(int i = 1;i<=T->keyNum;i++){
            printf("%d ",T->keys[i]);
        }
        printf("\n");
        for(int i = 0;i<T->childNum;i++){
            printTree(T->children[i]);
        }
    }
}

int main()
{
    Node* T = initNode(5);
    insert(&T, 1);
    insert(&T, 2);
    insert(&T, 3);
    insert(&T, 4);
    insert(&T, 5);
    insert(&T, 6);
    insert(&T, 7);
    insert(&T, 8);
    insert(&T, 9);
    insert(&T, 10);
    insert(&T, 11);
    insert(&T, 12);
    insert(&T, 13);
    insert(&T, 14);
    insert(&T, 15);
    insert(&T, 16);
    insert(&T, 17);
    insert(&T, 18);
    insert(&T, 19);
    insert(&T, 20);
    insert(&T, 21);
    insert(&T, 22);
    insert(&T, 23);
    insert(&T, 24);
    printTree(T);
    return 0;
}