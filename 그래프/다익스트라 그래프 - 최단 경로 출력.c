#include <stdio.h>

#define INT_MAX 2147483647 //�ִ� ����
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 7 //������ ��
#define INF 1000 //���Ѵ�(������ ���� ���)

int weight[MAX_VERTICES][MAX_VERTICES] = {//��Ʈ��ũ�� ���� ���
	{0,7,INF,INF,3,10,INF},
	{7,0,4,10,2,6,INF},
	{ INF,4,0,2,INF,INF,INF},
	{ INF,10,2,0,11,9,4},
	{3,2,INF,11,0,INF,5},
	{10,6,INF,9,INF,0,INF},
	{ INF,INF,INF,4,5,INF,0} };

int distance[MAX_VERTICES]; //���� �������κ����� �ִ� ��� �Ÿ�
int found[MAX_VERTICES]; //�湮�� ���� ǥ��
/*�߰� �� �κ�*/
int renew[MAX_VERTICES][MAX_VERTICES]; //���ŵ� ���� ����
int check[MAX_VERTICES];//�� �������� ���� ������ ǥ��

/*�߰� �� �κ�*/
//���ŵ� ���� ���� ����� �ʱ�ȭ (���Ѵ��)
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
	for (i = 0; i < n; i++) //�ʱ�ȭ
	{
		distance[i] = weight[start][i];
		found[i] = FALSE;
		/*�߰� �� �κ�*/
		check[i] = 1;
		renew[i][0] = start; // ���� ���� 0���� �ʱ�ȭ
	}
	found[start] = TRUE; //���� ���� �湮 ǥ��
	distance[start] = 0;
	for (i = 0; i < n - 2; i++)
	{
		u = choose(distance, n, found);
		found[u] = TRUE;
		for (w = 0; w < n; w++)
		{
			if (!found[w])
			{
				if (distance[u] + weight[u][w] < distance[w]) //����
				{
					/*�߰� �� �κ�*/
					if (i == 0)
					{
						renew[w][check[w]] = u; //���ŵ� ��θ� ����
						check[w]++; //�ش� renew���� ���� ���� �Ѿ�� ���ؼ�
					}
					else {
						for (j = 0; j < (check[u] + 1); j++) //renew�� ���� ����Ǿ��ִ� ���� �ִ� �� ���� �ݺ�
						{
							renew[w][j] = renew[u][j]; // w���� renew�� u���� renew�� �Ȱ��� �������
							renew[w][j + 1] = u; //w���� renew�� ���κ�(u��� ������ �κ� ����)�� ���ŵ� ���� ���� 
							check[w]++; //renew�� w�� �κп��� ���� ���� �Ѿ�� ���ؼ�   (w���� ���̸� ������)
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
	printf("���� ���� 0�������� �������� �ִܰ�θ� ���ϰڽ��ϱ� >> ");
	scanf_s("%d", &i);

	printf("0���� %d������ ��� : ", i);
	for (j = 0; j < MAX_VERTICES; j++) {
		if (renew[i][j] != INF) {
			printf("%d->", renew[i][j]);//����� ��θ� ����Ѵ�
		}
	}
	printf("%d\n", i); //������
}

/*�ַ��*/
//
//		����� �ϳ� �� �����, ���ŵǾ��� �� �湮�ϴ� ����� ���� �����Ѵ�.
//		���⼭ ������ �ִ� ��θ� ���ϱ� ����, �� ���� ���� ���� ã���� �� �ȴ�. (���ŵǴ� ���� = ���� ����ġ, �ִ� ��� ���� ���� ����)
//		## renew[���� ����][���ŵ� ����] 
//		renew�� ����ϸ� �ִ� ��θ� ���
//

/*���� ����� renew�� ���*/
//0  : 0
//1  : 0 4
//2  : 0 4 1
//3  : 0 4 1 2
//4  : 0
//5  : 0
//6  : 0 4

/*check �迭�� ���*/
//  1 2 3 6 1 1 2
