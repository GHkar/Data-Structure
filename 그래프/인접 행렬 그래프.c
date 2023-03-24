#include<stdio.h>
/*인접 행렬을 이용한 그래프 추상 데이터 타입의 구현*/
#define MAX_VERTICES 50
typedef struct GraphType {
	int n;//정점의 개수
	int adj_mat[MAX_VERTICES][MAX_VERTICES]; //50x50의 행렬 선언
}GraphType;

//그래프 초기화
void graph_init(GraphType *g)
{
	int r, c;
	g->n = 0;
	for (r = 0; r < MAX_VERTICES; r++)
	{
		for (c = 0; c < MAX_VERTICES; c++)
		{
			g->adj_mat[r][c] = 0;
		}
	}
}
//정점 삽입 연산
void insert_vertex(GraphType *g, int v)
{
	if (((g->n) + 1) > MAX_VERTICES)
	{
		fprintf(stderr, "그래프: 정점의 개수초과");
		return;
	}
	g->n++; //그냥 차례대로 삽입
}

//간선 삽입 연산
void insert_edge(GraphType *g, int start, int end)
{
	if (start >= g->n || end >= g->n)
	{
		fprintf(stderr, "그래프:정점 번호 오류");
		return;
	}
	g->adj_mat[start][end] = 1;
	g->adj_mat[end][start] = 1;
	//대칭이기 때문에 둘 다 만들어줌
}
