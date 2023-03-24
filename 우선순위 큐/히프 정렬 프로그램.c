#include<stdio.h>
#define MAX_ELEMENT 200

typedef struct {
	int key;
}element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;


//초기화 함수
init(HeapType *h)
{
	h->heap_size = 0;
}
//삽입 함수
void insert_max_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	//트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;	//새로운 노드를 삽입 
}
//삭제 함수
element delete_max_heap(HeapType *h)
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
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// 한단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
//우선순위 큐인 히프를 이용한 정렬
void heap_sort(element a[], int n)
{
	int i;
	HeapType h;

	init(&h);
	for (i = 0; i < n; i++) {
		insert_max_heap(&h, a[i]);
	}
	for (i = (n-1); i >= 0; i--) {
		a[i] = delete_max_heap(&h, a[i]);
	}
}
//주함수
void main()
{
	int i;
	int heapNUM = 3;
	element heapArr[3] = { 5, 9, 4 };
	heap_sort(heapArr, heapNUM);

	for (i = 0; i < heapNUM; i++) {
		printf("< %d > ", heapArr[i].key);
	}
}
