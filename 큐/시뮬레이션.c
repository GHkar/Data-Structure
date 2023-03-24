#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TRUE 1
#define FALSE 0
#define MAX_QUEUE_SIZE 100

typedef struct{
	int id;
	int arrival_time;
	int service_time;
}element;


typedef struct{ 
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

QueueType queue;


//���� ó�� �Լ�
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
//
int is_empty(QueueType *q)
{
	return (q->front == q->rear);
}
//���� ���� ���� �ռ�
int is_full(QueueType *q)
{
	return((q->rear + 1) % MAX_QUEUE_SIZE == q->front);
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
//0���� 1������ �Ǽ� ���� ���� �Լ�
double random()
{
	return rand() / (double)RAND_MAX;
}
//�ùķ��̼ǿ� �ʿ��� ���� ���� ���� ����
int duration = 10;			//�ùķ��̼� �ð�
double arrival_prob = 0.7;  // �ϳ��� �ð� ������ �����ϴ� ��� ���� ��
int max_serv_time = 5;		//�ϳ��� ���� ���� �ִ� ���� �ð�
int clock;

//�ùķ��̼��� ���
int customers;				//��ü �� ��
int served_customers;		//���񽺹��� �� ��
int waited_time;			//������ ��ٸ� �ð�

//���� ���ڸ� �����Ͽ� ���� �����ߴ��� �������� �ʾҴ����� �Ǵ�
int is_customer_arrived()
{
	if (random() < arrival_prob)
		return TRUE;
	else return FALSE;
}
//���� ������ ���� ť�� ����
void insert_customer(int arrival_time)
{
	element customer;

	customer.id = customers++;
	customer.arrival_time = arrival_time;
	customer.service_time = (int)(max_serv_time*random()) + 1;
	enqueue(&queue, customer);
	printf("���� %d�� %d�п� ���ɴϴ�. ���� �ð��� %d���Դϴ�.\n", customer.id, customer.arrival_time, customer.service_time);
}
//ť���� ��ٸ��� ���� ������ ���� ���� �ð��� ��ȯ�Ѵ�.
int remove_customer()
{

	element customer;
	int service_time = 0;

	if (is_empty(&queue)) return 0;
	customer = dequeue(&queue);
	service_time = customer.service_time - 1;
	served_customers++;
	waited_time += clock - customer.arrival_time;
	printf("�� %d�� %d�п� ���񽺸� �����մϴ�.��� �ð��� %d���̾����ϴ�.\n", customer.id, clock, clock-customer.arrival_time);
	return service_time;
}

//���ġ�� ����Ѵ�.
print_stat()
{
	printf("���񽺹��� ���� = %d\n", served_customers);
	printf("��ü ��� �ð� = %d��\n", waited_time);
	printf("1�δ� ��� ��� �ð�=%f��\n", (double)waited_time / served_customers);
	printf("���� ������� ���� = %d\n", customers - served_customers);
}
//�ùķ��̼� ���α׷�
void main()
{
	int service_time = 0;
	clock = 0;
	while (clock < duration) {
		clock++;
		printf("����ð�=%d\n", clock);
		if (is_customer_arrived()) {
			insert_customer(clock);
		}
		if (service_time > 0)
			service_time--;
		else {
			service_time = remove_customer();
		}
	}
	print_stat();
}
