#include<stdio.h>

#define BUCKETS 10
#define DIGITS 4
#define MAX_QUEUE_SIZE 100

typedef int element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

int list[] = { 3,2,5,1,10,8,9,4,7 };
//
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}

//초기화 함수 
void init(QueueType *q)
{
	q->front = q->rear = 0;
}
//공백 상태 검출 함수
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
//포화 상태 검출 함수
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
//삽입 함수
void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		error("큐가 포화상태입니다.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
//삭제 함수
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];

}
//피크 함수
element peek(QueueType *q)
{
	if (is_empty(q))
		error("큐가 공백상태입니다.");
	return q->queue[(q->front + 1) % MAX_QUEUE_SIZE];
}

void radix_sort(int list[], int n)
{
	int i, b, d, factor = 1;
	QueueType queues[BUCKETS];

	for (b = 0; b < BUCKETS; b++) {
		init(&queues[b]);
	}
	for (d = 0; d < DIGITS; d++) {
		for (i = 0; i < n; i++) {
			enqueue(&queues[(list[i] / factor) % 10], list[i]);
		}
		for (b = i = 0; b < BUCKETS; b++) {
			while (!is_empty(&queues[b])) {
				list[i++] = dequeue(&queues[b]);
			}
		}
		factor *= 10;
	}
}

void main() {
	radix_sort(&list, 10);
	for (int i = 0; i < 10; i++) {
		printf("%d ", list[i]);
	}
}

