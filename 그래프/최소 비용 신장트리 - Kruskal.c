#include<stdio.h>
#define MAX_VERTICES 100
#define INF 1000
#define TRUE 1
#define FALSE 0

// Union-find ���α׷� ����
int parent[MAX_VERTICES]; //�θ���
int num[MAX_VERTICES]; //�� ������ ũ��
//�ʱ�ȭ
void set_init(int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		parent[i] = -1; //������ �θ�� -1�� ����
		num[i] = 1; //���� �ϳ��� ����
	}
}
//vertex�� ���ϴ� ������ ��ȯ�Ѵ�.
int set_find(int vertex)
{
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p)
	{
		; //��Ʈ������ �ƹ��͵� ���� �ʰ� ����ؼ� �ݺ� ������ �θ��� �ݺ�x
	}
	s = i; //������ ��ǥ ����
	for (i = vertex; (p = parent[i]) >= 0; i = p)
	{
		parent[i] = s;//���� ���� ��� ���ҵ��� �θ� ��ǥ ������ s �ϳ��� ���� �Ѵ�.
	}
	return s;
}
//�� ���� ���Ұ� ���� ������ ��ģ��.
void set_union(int s1, int s2)
{
	if (num[s1] < num[s2])
	{
		parent[s1] = s2; //������ ������ ���� �� ū ���� �θ�� �ΰ� , s2�� s1�� �θ� ��
		num[s2] += num[s1]; // ������ ũ�⸦ ���� ������
	}
	else {
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

//������ ��� Ÿ�� ����
typedef struct {
	int key; //������ ����ġ
	int u; //����1
	int v; //����2
}element;

//���α׷� 8.5 �߿��� �ּ� ���� ���α׷� ����
#define MAX_ELEMENT 100
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

//�ʱ�ȭ �Լ�
void init(HeapType *h)
{
	h->heap_size = 0;
}
//
int is_empty(HeapType *h)
{
	if (h->heap_size == 0)
		return TRUE;
	else
		return FALSE;
}
//���� �Լ�
void insert_min_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	//Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;	//���ο� ��带 ���� 
}
//���� �Լ�
element delete_min_heap(HeapType *h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1]; //������ �� + ������ ��
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		//���� ����� �ڽ� ��� �� �� ���� �ڽ� ��带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key <= h->heap[child].key) break;
		// �Ѵܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
//���� u�� ���� v�� �����ϴ� ����ġ�� weight�� ������ ������ ����
void insert_heap_edge(HeapType *h, int u, int v, int weight)
{
	element e;
	e.u = u;
	e.v = v;
	e.key = weight;
	insert_min_heap(h, e);
}
//���� ����̳� ���� ����Ʈ���� �������� �о �ּ� ������ ����
void insert_all_edges(HeapType *h)
{
	insert_heap_edge(h, 0, 1, 29);
	insert_heap_edge(h, 1, 2, 16);
	insert_heap_edge(h, 2, 3, 12);
	insert_heap_edge(h, 3, 4, 22);
	insert_heap_edge(h, 4, 5, 27);
	insert_heap_edge(h, 5, 0, 10);
	insert_heap_edge(h, 6, 1, 15);
	insert_heap_edge(h, 6, 3, 18);
	insert_heap_edge(h, 6, 4, 25);
}
//kruskal�� �ּ� ��� ���� Ʈ�� ���α׷�
void kruskal(int n)
{
	int edge_accepted = 0; //������� ���õ� ������ ��
	HeapType h;//�ּ� ����
	int uset, vset; //���� u�� ���� v�� ���� ��ȣ
	element e; //���� ���

	init(&h); //���� �ʱ�ȭ
	insert_all_edges(&h);//������ �������� ����
	set_init(n); //���� �ʱ�ȭ
	while (edge_accepted < (n - 1))//������ �� < (n-1) �ּ� ��� ����Ʈ���� n-1���� ������ ���´�.
	{
		e = delete_min_heap(&h);//�ּ� �������� ����
		uset = set_find(e.u);//���� u�� ���� ��ȣ
		vset = set_find(e.v);//���� v�� ���� ��ȣ
		if (uset != vset) { //���� ���� ������ �ٸ���, �� �θ� �ٸ���
			printf("(%d, %d)  %d \n", e.u, e.v, e.key);
			edge_accepted++;
			set_union(uset, vset); //�� ���� ������ ��ģ��.
		}
	}
}
//
main()
{
	kruskal(7);
}

