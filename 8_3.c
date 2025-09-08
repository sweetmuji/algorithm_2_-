#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode* left;
    struct TreeNode* right; 
} TreeNode;

void inorder(TreeNode* root) // 중위 순회 LVR
{
    if(root != NULL)
    {
        inorder(root->left);
        printf("[ %d ] ", root->data);
        inorder(root->right);
    }
}

void preorder(TreeNode* root) // 전위 순회 VLR 
{
    if(root != NULL)
    {
        printf("[ %d ] ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(TreeNode* root) // 후위 순회 LRV
{
    if (root != NULL)
    {
        postorder(root->left);
        postorder(root->right);
        printf("[ %d ] ", root->data);
    }
}

int main(void)
{
    TreeNode n1 = { 1, NULL, NULL };
    TreeNode n2 = { 4, &n1, NULL };
    TreeNode n3 = { 16, NULL, NULL };
    TreeNode n4 = { 25, NULL, NULL };
    TreeNode n5 = { 20, &n3, &n4 };
    TreeNode n6 = { 15, &n2, &n5 };

    TreeNode* root = &n6;

    printf("중위 순회 = ");
    inorder(root);
    printf("\n");

    printf("전위 순회 = ");
    preorder(root);
    printf("\n");

    printf("후위 순회 = ");
    postorder(root);
    printf("\n");

    return 0;
}