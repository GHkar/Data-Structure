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
	{ INF,INF,INF,4,5,INF,0} };

int distance[MAX_VERTICES]; //시작 정점으로부터의 최단 경로 거리
int found[MAX_VERTICES]; //방문한 정점 표시
/*추가 된 부분*/
int renew[MAX_VERTICES][MAX_VERTICES]; //갱신된 정점 저장
int check[MAX_VERTICES];//한 정점으로 가는 정점을 표시

/*추가 된 부분*/
//갱신된 정점 저장 행렬을 초기화 (무한대로)
void init_renew(int renew[][MAX_VERTICES]) {
	int i, j;
	for (i = 0; i < MAX_VERTICES; i++) {
		for (j = 0; j < MAX_VERTICES; j++) {
			renew[i][j] = INF;
		}
	}
}


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
	int i, j, u, w;
	for (i = 0; i < n; i++) //초기화
	{
		distance[i] = weight[start][i];
		found[i] = FALSE;
		/*추가 된 부분*/
		check[i] = 1;
		renew[i][0] = start; // 시작 정점 0으로 초기화
	}
	found[start] = TRUE; //시작 정점 방문 표시
	distance[start] = 0;
	for (i = 0; i < n - 2; i++)
	{
		u = choose(distance, n, found);
		found[u] = TRUE;
		for (w = 0; w < n; w++)
		{
			if (!found[w])
			{
				if (distance[u] + weight[u][w] < distance[w]) //갱신
				{
					/*추가 된 부분*/
					if (i == 0)
					{
						renew[w][check[w]] = u; //갱신된 경로를 저장
						check[w]++; //해당 renew행의 다음 열로 넘어가기 위해서
					}
					else {
						for (j = 0; j < (check[u] + 1); j++) //renew의 열에 저장되어있는 값이 있는 곳 까지 반복
						{
							renew[w][j] = renew[u][j]; // w행의 renew를 u행의 renew로 똑같이 만들어줌
							renew[w][j + 1] = u; //w행의 renew열 끝부분(u행과 같아진 부분 다음)에 갱신된 값을 넣음 
							check[w]++; //renew의 w행 부분에서 다음 열로 넘어가기 위해서   (w행의 길이를 정해줌)
						}
					}
					distance[w] = distance[u] + weight[u][w];
				}
			}
		}
	}
}

void main()
{
	init_renew(renew);
	int i, j;
	shortest_path(0, MAX_VERTICES);
	printf("시작 정점 0에서부터 어디까지의 최단경로를 구하겠습니까 >> ");
	scanf_s("%d", &i);

	printf("0에서 %d까지의 노드 : ", i);
	for (j = 0; j < MAX_VERTICES; j++) {
		if (renew[i][j] != INF) {
			printf("%d->", renew[i][j]);//저장된 경로를 출력한다
		}
	}
	printf("%d\n", i); //마지막
}

/*솔루션*/
//
//		행렬을 하나 더 만들어, 갱신되었을 때 방문하는 노드의 값을 저장한다.
//		여기서 갱신은 최단 경로를 구하기 위해, 즉 가장 작은 값을 찾았을 때 된다. (갱신되는 정점 = 작은 가중치, 최단 경로 값을 가진 정점)
//		## renew[도착 정점][갱신된 정점] 
//		renew를 출력하면 최단 경로를 출력
//

/*최종 저장된 renew의 모습*/
//0  : 0
//1  : 0 4
//2  : 0 4 1
//3  : 0 4 1 2
//4  : 0
//5  : 0
//6  : 0 4

/*check 배열의 모습*/
//  1 2 3 6 1 1 2
