//LinkedQueue.c

#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef int element;
typedef struct QueueNode{
	element item;
	struct QueueNode *link;
} QueueNode;

typedef struct{
	QueueNode *front, *rear;
} QueueType;

void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

void init(QueueType *q)
{
	q->front = q->rear = NULL;
}

int is_empty(QueueType *q)
{
	return (q->front==NULL);
}

void enqueue(QueueType *q, element item)
{
	QueueNode *temp=(QueueNode *)malloc(sizeof(QueueNode));
	if(temp ==NULL)
		error("메모리를 할당할 수 없습니다");
	else{
		temp->item = item;
		temp->link = NULL;
		if(is_empty(q) ){
			q->front = temp;
			q->rear = temp;
		}
		else{
			q->rear->link = temp;
			q->rear = temp;
		}
	}
}

element dequeue(QueueType *q)
{
	QueueNode *temp = q->front;
	element item;
	if(is_empty(q))
		error("큐가 비어 있습니다.");
	else{
		item = temp->item;
		q->front = q->front->link;
		if(q->front == NULL)
			q->rear = NULL;
		free(temp);
		return item;
	}
}

element peek(QueueType *q)
{
	if(is_empty(q))
		error("큐가 비어 있습니다.");
	else{
		return q->front->item;
	}
}


int main()
{

	QueueType q;
	init(&q);
	int i= 0;
	
	enqueue(&q, 0);
	enqueue(&q, 1);
	printf("0\n");
	
	for(i=0; i<=10; i++){
	
		enqueue(&q, dequeue(&q) + peek(&q));
		printf("%d\n", peek(&q));
		
	}
	
	
}

