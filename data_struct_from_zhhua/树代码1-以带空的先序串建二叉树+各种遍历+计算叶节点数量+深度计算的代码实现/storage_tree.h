typedef char TElemType;
typedef struct BiTNode { // ���ṹ
    TElemType      data;
    struct BiTNode  *lchild, *rchild; // ���Һ���ָ��                                  
} BiTNode, *BiTree;