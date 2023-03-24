#include <stdio.h>
#include <memory.h>
#include <malloc.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 100


typedef struct TreeNode{
	int data;
	struct TreeNode *left, *right;
}TreeNode;

TreeNode n1={1, NULL, NULL};
TreeNode n2={4, &n1, NULL};
TreeNode n3={16, NULL, NULL};
TreeNode n4={25, NULL, NULL};
TreeNode n5={20, &n3, &n4};
TreeNode n6={15, &n2, &n5};
TreeNode *root= &n6;

//���� ��ȸ 
void inorder (TreeNode *root){
	if(root){
		inorder( root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}
//���� ��ȸ 
void preorder (TreeNode *root){
	if(root){
		printf("%d ", root->data);
		inorder( root->left);
		inorder(root->right);
	}
}
//���� ��ȸ 
void postorder (TreeNode *root){
	if(root){
		inorder( root->left);
		inorder(root->right);
		printf("%d ", root->data);
	}
}

//���� ��ȸ ���α׷� 
typedef TreeNode *element;
//����  ť 
typedef struct{
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;
//
void error(char *message)
{
	fprintf(stderr,"%s\n", message);
	exit(1);
}
//�ʱ�ȭ �Լ�
void init(QueueType *q)
{
	q->front = q->rear=0;
}
//���� ���� ���� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
//��ȭ ���� ���� �Լ�
int is_full(QueueType *q)
{
	return ((q->rear+1)%MAX_QUEUE_SIZE == q->front);
}
//���� �Լ�
void enqueue(QueueType *q, element item)
{
	if(is_full(q))
		error("ť�� ��ȭ�����Դϴ�.");
	q->rear = (q->rear+1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
//���� �Լ�
element dequeue(QueueType *q)
{
	if(is_empty(q))
		error("ť�� ��������Դϴ�.");
	q->front=(q->front+1)%MAX_QUEUE_SIZE;
	return q->queue[q->front];

}
//��ũ �Լ�
element peek(QueueType *q)
{
	if(is_empty(q))
		error("ť�� ��������Դϴ�.");
	return q->queue[(q->front+1)%MAX_QUEUE_SIZE];
}

//���� ��ȸ 
void level_order(TreeNode *ptr)
{
	QueueType q;
	
	init(&q);
	if(ptr == NULL) return;
	enqueue(&q, ptr);
	while(!is_empty(&q)){
		ptr = dequeue(&q);
		printf("%d ", ptr->data);
		if(ptr->left)
			enqueue(&q, ptr->left);
		if(ptr->right)
			enqueue(&q, ptr->right);
	}
}

void main()
{
	printf("���� ��ȸ\n");
	inorder(root);
	printf("\n");
	printf("���� ��ȸ\n");
	preorder(root);
	printf("\n");
	printf("���� ��ȸ\n");
	postorder(root);
	printf("\n");
	printf("���� ��ȸ\n");
	level_order(root);
	printf("\n");
}
