#include <stdio.h>

#define INT_MAX 2147483647 //최대 정수
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 7 //정점의 수
#define INF 1000 //무한대(연결이 없는 경우)

int weight[MAX_VERTICES][MAX_VERTICES] = {//네트워크의 인접 행렬
	{0,7,INF,INF,3,10,INF},
	{7,0,4,10,2,6,INF},
	{ INF,4,0,2,INF,INF,INF},
	{ INF,10,2,0,11,9,4},
	{3,2,INF,11,0,INF,5},
	{10,6,INF,9,INF,0,INF},
	{ INF,INF,INF,4,5,INF,0}};

int distance[MAX_VERTICES]; //시작 정점으로부터의 최단 경로 거리
int found[MAX_VERTICES]; //방문한 정점 표시

int choose(int distance[], int n, int found[])
{
	int i, min, minpos;
	min = INT_MAX;
	minpos = -1;
	for (i = 0; i < n; i++)
	{
		if (distance[i] < min && !found[i]) {
			min = distance[i];
			minpos = i;
		}
	}
	return minpos;
}

void shortest_path(int start, int n)
{
	int i, u, w;
	for (i = 0; i < n; i++) //초기화
	{
		distance[i] = weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE; //시작 정점 방문 표시
	distance[start] = 0;
	for (i = 0; i < n - 1; i++)
	{
		u = choose(distance, n, found);
		found[u] = TRUE;
		for (w = 0; w < n; w++)
		{
			if (!found[w])
			{
				if (distance[u] + weight[u][w] < distance[w])
				{
					distance[w] = distance[u] + weight[u][w];
				}
			}
		}
	}
	//최종 거리 출력
	printf("최종 거리는 -> ");
	for (i = 0; i < n; i++) {
		printf("%d ", distance[i]);
	}
	printf("\n");
}

int main()
{
	shortest_path(0, MAX_VERTICES);
}
