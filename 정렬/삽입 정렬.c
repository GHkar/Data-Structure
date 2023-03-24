#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

int list[MAX_SIZE];
int n;

//���� ���� 
void insertion_sort(int list[], int n) {
	int i, j, key, p;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i-1; j >= 0 && list[j] > key; j--) {//���ǹ� ���� �������� Ȯ�� ��
			list[j + 1] = list[j];
		}
		list[j + 1] = key;
		for (p = 0; p < n; p++) {
			printf("%d ", list[p]);
		}
		printf("\n");
	}
}
void main()
{
	int i;
	n = MAX_SIZE;
	for (i = 0; i < n; i++) {
		list[i] = rand() % n;
	}
	insertion_sort(list, n);
}
