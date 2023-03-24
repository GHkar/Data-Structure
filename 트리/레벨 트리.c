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

//전위 순회 
void inorder (TreeNode *root){
	if(root){
		inorder( root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}
//중위 순회 
void preorder (TreeNode *root){
	if(root){
		printf("%d ", root->data);
		inorder( root->left);
		inorder(root->right);
	}
}
//후위 순회 
void postorder (TreeNode *root){
	if(root){
		inorder( root->left);
		inorder(root->right);
		printf("%d ", root->data);
	}
}

//레벨 순회 프로그램 
typedef TreeNode *element;
//원형  큐 
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
//초기화 함수
void init(QueueType *q)
{
	q->front = q->rear=0;
}
//공백 상태 검출 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
//포화 상태 검출 함수
int is_full(QueueType *q)
{
	return ((q->rear+1)%MAX_QUEUE_SIZE == q->front);
}
//삽입 함수
void enqueue(QueueType *q, element item)
{
	if(is_full(q))
		error("큐가 포화상태입니다.");
	q->rear = (q->rear+1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
//삭제 함수
element dequeue(QueueType *q)
{
	if(is_empty(q))
		error("큐가 공백상태입니다.");
	q->front=(q->front+1)%MAX_QUEUE_SIZE;
	return q->queue[q->front];

}
//피크 함수
element peek(QueueType *q)
{
	if(is_empty(q))
		error("큐가 공백상태입니다.");
	return q->queue[(q->front+1)%MAX_QUEUE_SIZE];
}

//레벨 순회 
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
	printf("전위 순회\n");
	inorder(root);
	printf("\n");
	printf("중위 순회\n");
	preorder(root);
	printf("\n");
	printf("후위 순회\n");
	postorder(root);
	printf("\n");
	printf("레벨 순회\n");
	level_order(root);
	printf("\n");
}
