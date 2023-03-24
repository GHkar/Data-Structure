#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10
#define SWAP(x,y,t) ((t)=(x), (x)=(y), (y)=(t))

int list[MAX_SIZE];
int n;

//선택 정렬 
void selection_sort(int list[], int n) {
	int i, j, least, temp;
	for (i = 0; i < n - 1; i++) {
		least = i;
		for (j = i + 1; j < n; j++) {
			if (list[j] < list[least]) least = j;
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
		printf("%d ", list[i]);
	}
}
