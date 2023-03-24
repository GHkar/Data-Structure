#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

typedef struct TreeNode {
	int data;
	struct TreeNode *left, *right;
}TreeNode;

TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
TreeNode *root = &n6;

//중위 순회
void inorder(TreeNode *root) {
	if (root) {
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

//전위 순회
void preorder(TreeNode *root) {
	if (root) {
		printf("%d ", root->data);
		inorder(root->left);
		inorder(root->right);
	}
}

//후위 순회
void postorder(TreeNode *root) {
	if (root) {
		inorder(root->left);
		inorder(root->right);
		printf("%d ", root->data);
	}
}

//주 함수
void main()
{
	inorder(root);
	printf("\n");
	preorder(root);
	printf("\n");
	postorder(root);
	printf("\n");
}
