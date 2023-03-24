#include<stdio.h>
/*인접 리스트를 이용한 그래프 추상 데이터 타입의 구현*/


#define MAX_VERTICES 50 //정점 최대 갯수

typedef struct GraphNode //그래프 노드 하나 만들기
{
	int vertex;//정점 값을 담을 곳
	struct GraphNode *link; //주소를 담을 링크
}GraphNode;

typedef struct GraphType //그래프의 그릇 만들기
{
	int n; //정점의 개수
	GraphNode *adj_list[MAX_VERTICES]; //GraphNode를 50개 생성
}GraphType;

//그래프 초기화
void graph_init(GraphType *g)
{
	int v; // 단순 변수
	g->n = 0; //정점의 개수 0개로 초기화
	for (v = 0; v < MAX_VERTICES; v++)
	{
		g->adj_list[v] = NULL; //생성된 GraphNode 50개의 모든 값들을 초기화
	}
}

//정점 삽입 연산
void insert_vertex(GraphType *g, int v)
{
	//50개보다 더 많은 값을 넣으려 하면
	if ((g->n) + 1 > MAX_VERTICES)
	{
		fprintf(stderr, "그래프: 정점의 개수 초과");
		return;
	}
	g->n++;//총 개수 증가
}

//간선 삽입 연산, v를 u의 인접 리스트에 삽입한다
void insert_edge(GraphType *g, int u, int v)
{
	GraphNode *node;
	if (u >= g->n || v >= g->n) // 총 정점의 갯수, 즉 들어있는 정점의 최대값보다 큰값을 넣는다면, 잘못 입력한 것
	{
		fprintf(stderr, "그래프: 정점 번호 오류");
		return;
	}
	node = (GraphNode *)malloc(sizeof(GraphNode));
	node->vertex = v; //연결 되어 있는 노드의 값
	node->link = g->adj_list[u]; //u는 헤드 노드, 미리 만들어 놓은 헤드노드의 위치의 값을 링크에 넣어 가리키게 함
	g->adj_list[u] = node;//헤드노드 역시 새 노드를 가리킴
}
