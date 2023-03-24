#include <stdio.h>

#define INT_MAX 2147483647 //�ִ� ����
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 7 //������ ��
#define INF 1000 //���Ѵ�(������ ���� ���)

int weight[MAX_VERTICES][MAX_VERTICES] = {//��Ʈ��ũ�� ���� ���
	{ 0,7,INF,INF,3,10,INF },
{ 7,0,4,10,2,6,INF },
{ INF,4,0,2,INF,INF,INF },
{ INF,10,2,0,11,9,4 },
{ 3,2,INF,11,0,INF,5 },
{ 10,6,INF,9,INF,0,INF },
{ INF,INF,INF,4,5,INF,0 } };

int distance[MAX_VERTICES]; //���� �������κ����� �ִ� ��� �Ÿ�
int found[MAX_VERTICES]; //�湮�� ���� ǥ��
int path[MAX_VERTICES]; //path �迭 �ϳ� ����

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
	for (i = 0; i < n; i++) //�ʱ�ȭ
	{
		distance[i] = weight[start][i];
		found[i] = FALSE;
	}
	found[start] = TRUE; //���� ���� �湮 ǥ��
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
					path[w] = u; //path�迭�� ���ŵǴ� u ���� �ִ´�
				}
			}
		}
	}
	//���� �Ÿ� ���
	printf("���� �Ÿ��� -> ");
	for (i = 0; i < n; i++) {
		printf("%d ", distance[i]);
	}
	printf("\n");
}

int main()
{
	int i, s;
	int z[MAX_VERTICES];

	shortest_path(0, MAX_VERTICES);

	printf("�������� ��θ� ����Ͻðڽ��ϱ� >> ");
	scanf_s("%d", &s);
	for (i = 0; i < MAX_VERTICES; i++)
	{
		if (path[s] == 0) break;
		printf("%d ", path[s]);
		s = path[s];
	}
}
