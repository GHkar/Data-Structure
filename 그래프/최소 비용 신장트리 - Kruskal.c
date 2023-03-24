#include<stdio.h>
#define MAX_VERTICES 100
#define INF 1000
#define TRUE 1
#define FALSE 0

// Union-find 프로그램 삽입
int parent[MAX_VERTICES]; //부모노드
int num[MAX_VERTICES]; //각 집합의 크기
//초기화
void set_init(int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		parent[i] = -1; //본인이 부모면 -1을 갖음
		num[i] = 1; //본인 하나만 있음
	}
}
//vertex가 속하는 집합을 반환한다.
int set_find(int vertex)
{
	int p, s, i = -1;
	for (i = vertex; (p = parent[i]) >= 0; i = p)
	{
		; //루트노드까지 아무것도 하지 않고 계속해서 반복 본인이 부모라면 반복x
	}
	s = i; //집합의 대표 원소
	for (i = vertex; (p = parent[i]) >= 0; i = p)
	{
		parent[i] = s;//집합 내의 모든 원소들의 부모를 대표 원소인 s 하나로 통일 한다.
	}
	return s;
}
//두 개의 원소가 속한 집합을 합친다.
void set_union(int s1, int s2)
{
	if (num[s1] < num[s2])
	{
		parent[s1] = s2; //보유한 집합의 수가 더 큰 수를 부모로 두고 , s2가 s1의 부모가 됨
		num[s2] += num[s1]; // 집합의 크기를 증가 시켜줌
	}
	else {
		parent[s2] = s1;
		num[s1] += num[s2];
	}
}

//히프의 요소 타입 정의
typedef struct {
	int key; //간선의 가중치
	int u; //정점1
	int v; //정점2
}element;

//프로그램 8.5 중에서 최소 히프 프로그램 삽입
#define MAX_ELEMENT 100
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;

//초기화 함수
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
//삽입 함수
void insert_min_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	//트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;	//새로운 노드를 삽입 
}
//삭제 함수
element delete_min_heap(HeapType *h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1]; //리턴할 값 + 삭제할 값
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		//현재 노드의 자식 노드 중 더 작은 자식 노드를 찾는다.
		if ((child < h->heap_size) &&
			(h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key <= h->heap[child].key) break;
		// 한단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
//정점 u와 정점 v를 연결하는 가중치가 weight인 간선을 히프에 삽입
void insert_heap_edge(HeapType *h, int u, int v, int weight)
{
	element e;
	e.u = u;
	e.v = v;
	e.key = weight;
	insert_min_heap(h, e);
}
//인접 행렬이나 인접 리스트에서 간선들을 읽어서 최소 히프에 삽입
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
//kruskal의 최소 비용 신장 트리 프로그램
void kruskal(int n)
{
	int edge_accepted = 0; //현재까지 선택된 간선의 수
	HeapType h;//최소 히프
	int uset, vset; //정점 u와 정점 v의 집합 번호
	element e; //히프 요소

	init(&h); //히프 초기화
	insert_all_edges(&h);//히프에 간선들을 삽입
	set_init(n); //집합 초기화
	while (edge_accepted < (n - 1))//간선의 수 < (n-1) 최소 비용 신장트리는 n-1개의 간선이 나온다.
	{
		e = delete_min_heap(&h);//최소 히프에서 삭제
		uset = set_find(e.u);//정점 u의 집합 번호
		vset = set_find(e.v);//정점 v의 집합 번호
		if (uset != vset) { //서로 속한 집합이 다르면, 즉 부모가 다르면
			printf("(%d, %d)  %d \n", e.u, e.v, e.key);
			edge_accepted++;
			set_union(uset, vset); //두 개의 집합을 합친다.
		}
	}
}
//
main()
{
	kruskal(7);
}

