#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义二叉树节点结构
typedef struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// 函数用于在先序和中序序列中构建二叉树
TreeNode* buildTree(char *preorder, char *inorder, int len) {
    if (len <= 0) {
        return NULL;
    }

    TreeNode *node = (TreeNode *)malloc(sizeof(TreeNode));
    node->data = *preorder;
    node->left = node->right = NULL;

    char *inorderPos = strchr(inorder, *preorder);
    int leftSubtreeSize = inorderPos - inorder;

    node->left = buildTree(preorder + 1, inorder, leftSubtreeSize);
    node->right = buildTree(preorder + 1 + leftSubtreeSize, inorderPos + 1, len - leftSubtreeSize - 1);

    return node;
}

// 函数用于计算二叉树的深度
int treeDepth(TreeNode *root) {
    if (root == NULL) {
        return 0;
    }

    int leftDepth = treeDepth(root->left);   //递归求高度
    int rightDepth = treeDepth(root->right);

    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

// 函数用于计算二叉树的叶子节点数量
int leafNodeCount(TreeNode *root) {
    if (root == NULL) {
        return 0;
    }

    if (root->left == NULL && root->right == NULL) {
        return 1;
    }

    return leafNodeCount(root->left) + leafNodeCount(root->right);
}

int main() {
    char preorder[100]; // 先序遍历序列
    char inorder[100]; // 中序遍历序列
    
    scanf("%s", preorder);
    scanf("%s", inorder);

    int len = strlen(preorder);

    TreeNode *root = buildTree(preorder, inorder, len);

    int depth = treeDepth(root);
    int leafCount = leafNodeCount(root);

    printf("%d\n", depth);
    printf("%d\n", leafCount);

    return 0;
}
