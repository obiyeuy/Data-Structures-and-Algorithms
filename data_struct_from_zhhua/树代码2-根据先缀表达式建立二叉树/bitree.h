#define TRUE 1
#define FALSE 0
#define OK 1
typedef int Status;
typedef char TElemType;//����Ԫ������
typedef struct BiTNode { // ���ṹ
    TElemType      data;
    struct BiTNode  *lchild, *rchild; // ���Һ���ָ��                                  
} BiTNode, *BiTree;  //���ṹ�����ṹ
Status CreateBiTree(BiTree &T);//�����������׺���ʽ���� ���ʽ  -��+ a b c / d e
void PreOrder (BiTree T,void( *visit)(TElemType& e));//�ȸ�����
void InOrder (BiTree T,void( *visit)(TElemType& e));//�и�����
void PostOrder (BiTree T,void( *visit)(TElemType& e));//�������
void visit(TElemType& e);//���ʺ���
