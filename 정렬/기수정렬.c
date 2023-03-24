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

//�ʱ�ȭ �Լ� 
void init(QueueType *q)
{
	q->front = q->rear = 0;
}
//���� ���� ���� �Լ�
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
//��ȭ ���� ���� �Լ�
int is_full(QueueType *q)
{
	return ((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
}
//���� �Լ�
void enqueue(QueueType *q, element item)
{
	if (is_full(q))
		error("ť�� ��ȭ�����Դϴ�.");
	q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;
}
//���� �Լ�
element dequeue(QueueType *q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�.");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];

}
//��ũ �Լ�
element peek(QueueType *q)
{
	if (is_empty(q))
		error("ť�� ��������Դϴ�.");
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

