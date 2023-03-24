#include<stdio.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 50
#define MAX_QUEUE_SIZE 100

typedef int element;
typedef struct {
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

typedef struct GraphNode
{
	int vertex;
	struct GraphNode *link;
}GraphNode;

typedef struct GraphType
{
	int n; //������ ����
	GraphNode *adj_list[MAX_VERTICES];
}GraphType;

//�׷��� �ʱ�ȭ
void graph_init(GraphType *g)
{
	int v;
	g->n = 0;
	for (v = 0; v < MAX_VERTICES; v++)
	{
		g->adj_list[v] = NULL;
	}
}
//���� ���� ����
void insert_vertex(GraphType *g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES)
	{
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;
}
//���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�.
void insert_edge(GraphType *g, int u, int v)
{
	GraphNode *node;
	if (u >= g->n || v >= g->n) {
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	node = (GraphNode *)malloc(sizeof(GraphNode));
	node->vertex = v;
	node->link = g->adj_list[u];
	g->adj_list[u] = node;
}

/*******************************************/

//�湮�� ��带 �˱� ���� �迭 ����
int visited[MAX_VERTICES];
//ť �ҽ�
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

/*******************************************/

//�ʺ� �켱 Ž��(���� ����Ʈ)
void bfs_list(GraphType *g, int v)
{
	GraphNode *w;
	QueueType q;
	init(&q);//ť �ʱ�ȭ
	visited[v] = TRUE;//���� v �湮 ǥ��
	printf("%d ", v); //���� v ���
	enqueue(&q, v);//���� ������ ť�� ����
	while (!is_empty(&q))//ť�� ������� ������ ����ؼ� �ݺ�
	{
		v = dequeue(&q);//ť���� ���� ����
		for (w = g->adj_list[v]; w; w = w->link) //���� ���� Ž��
		{
			if (!visited[w->vertex])//�̹湮 ���� Ž��
			{
				visited[w->vertex] = TRUE;//�湮ǥ��
				printf("%d ", w->vertex);//���� ���
				enqueue(&q, w->vertex);//�湮�� ������ ť�� ����
			}
		}
	}
}

/*******************************************/

//���� �켱 Ž��
void dfs_list(GraphType *g, int v)
{
	GraphNode *w;
	visited[v] = TRUE; //���� v�� �湮 ǥ��
	printf("%d ", v);
	for (w = g->adj_list[v]; w; w = w->link)//���� ���� Ž��
	{
		if (!visited[w->vertex]) //�湮�� ��������
		{
			dfs_list(g, w->vertex); //��ȯ ȣ��
		}
	}
}

main()
{
	int i;
	GraphType g;

	graph_init(&g);
	//���� ����Ʈ
	for (i = 0; i < 6; i++)
	{
		insert_vertex(&g, i);
	}
	insert_edge(&g, 0, 1);
	insert_edge(&g, 1, 0);
	insert_edge(&g, 0, 2);
	insert_edge(&g, 2, 0);
	insert_edge(&g, 0, 4);
	insert_edge(&g, 4, 0);
	insert_edge(&g, 1, 2);
	insert_edge(&g, 2, 1);
	insert_edge(&g, 2, 3);
	insert_edge(&g, 3, 2);
	insert_edge(&g, 2, 4);
	insert_edge(&g, 4, 2);
	insert_edge(&g, 3, 4);
	insert_edge(&g, 4, 3);
	
	//����
	dfs_list(&g, 0);
	printf("\n");
	//visited�� ���ڵ��� �� 1�̱� ������ �湮�� ���� ��� 0���� ��µ�
	for (i = 0; i < 6; i++)
	{
		visited[i] = 0;
	}
	//�ʺ�
	bfs_list(&g, 0);
	printf("\n");
}
