#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10000
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

int list[MAX_SIZE];
int n;
//삽입 정렬
void insertion_sort(int list[], int n) {
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = list[i];
		for (j = i - 1; j > 0 && list[j] > key; j--) {//조건문 덕에 안정성이 확보 됨
			list[j + 1] = list[j];
		}
		list[j + 1] = key;
	}
}

//선택 정렬
void selection_sort(int list[], int n) {
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) {
			if (list[j] < list[j + 1]) least = j;
		}
		if (list[i] != list[least]) {
			SWAP(list[i], list[least], temp);
		}
	}
}

void main()
{
	int i;
	n = MAX_SIZE;
	for (i = 0; i < n; i++) {
		list[i] = rand() % n;
	}
	selection_sort(list, n);
	for (i = 0; i < n; i++) {
		printf("%d\n", list[i]);
	}
}
