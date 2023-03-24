#include<stdio.h>
/*���� ����Ʈ�� �̿��� �׷��� �߻� ������ Ÿ���� ����*/


#define MAX_VERTICES 50 //���� �ִ� ����

typedef struct GraphNode //�׷��� ��� �ϳ� �����
{
	int vertex;//���� ���� ���� ��
	struct GraphNode *link; //�ּҸ� ���� ��ũ
}GraphNode;

typedef struct GraphType //�׷����� �׸� �����
{
	int n; //������ ����
	GraphNode *adj_list[MAX_VERTICES]; //GraphNode�� 50�� ����
}GraphType;

//�׷��� �ʱ�ȭ
void graph_init(GraphType *g)
{
	int v; // �ܼ� ����
	g->n = 0; //������ ���� 0���� �ʱ�ȭ
	for (v = 0; v < MAX_VERTICES; v++)
	{
		g->adj_list[v] = NULL; //������ GraphNode 50���� ��� ������ �ʱ�ȭ
	}
}

//���� ���� ����
void insert_vertex(GraphType *g, int v)
{
	//50������ �� ���� ���� ������ �ϸ�
	if ((g->n) + 1 > MAX_VERTICES)
	{
		fprintf(stderr, "�׷���: ������ ���� �ʰ�");
		return;
	}
	g->n++;//�� ���� ����
}

//���� ���� ����, v�� u�� ���� ����Ʈ�� �����Ѵ�
void insert_edge(GraphType *g, int u, int v)
{
	GraphNode *node;
	if (u >= g->n || v >= g->n) // �� ������ ����, �� ����ִ� ������ �ִ밪���� ū���� �ִ´ٸ�, �߸� �Է��� ��
	{
		fprintf(stderr, "�׷���: ���� ��ȣ ����");
		return;
	}
	node = (GraphNode *)malloc(sizeof(GraphNode));
	node->vertex = v; //���� �Ǿ� �ִ� ����� ��
	node->link = g->adj_list[u]; //u�� ��� ���, �̸� ����� ���� ������� ��ġ�� ���� ��ũ�� �־� ����Ű�� ��
	g->adj_list[u] = node;//����� ���� �� ��带 ����Ŵ
}
