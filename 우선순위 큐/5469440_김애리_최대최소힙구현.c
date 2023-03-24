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
//최대 삽입 함수
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
//최대 삭제 함수
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


//최소 삽입 함수
void insert_min_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	//트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
	while ((i != 1) && (item.key < h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;	//새로운 노드를 삽입 
}
//최소 삭제 함수
element delete_min_heap(HeapType *h)
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
			(h->heap[child].key) > h->heap[child + 1].key)
			child++;
		if (temp.key <= h->heap[child].key) break;
		// 한단계 아래로 이동
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
//주함수
void main()
{
	element e1 = { 10 }, e2 = { 5 }, e3 = { 30 };
	element e4, e5, e6;   //delete의 값
	HeapType max_heap, min_heap;		//히프 생성
	init(&max_heap);				//최대 힙 초기화
	init(&min_heap);				//최소 힙 초기화
	//최대 삽입
	insert_max_heap(&max_heap, e1);
	insert_max_heap(&max_heap, e2);
	insert_max_heap(&max_heap, e3);
	//최소 삽입 
	insert_min_heap(&min_heap, e1);
	insert_min_heap(&min_heap, e2);
	insert_min_heap(&min_heap, e3);
	//print_heap(&heap); 

	//최대 삭제
	printf("최대 힙\n");
	e4 = delete_max_heap(&max_heap);
	printf("< %d > ", e4.key);
	e5 = delete_max_heap(&max_heap);
	printf("< %d > ", e5.key);
	e6 = delete_max_heap(&max_heap);
	printf("< %d > ", e6.key);
	printf("\n"); //둘 사이 구분
	//최소 삭제
	printf("최소 힙\n");
	e4 = delete_min_heap(&min_heap);
	printf("< %d > ", e4.key);
	e5 = delete_min_heap(&min_heap);
	printf("< %d > ", e5.key);
	e6 = delete_min_heap(&min_heap);
	printf("< %d > ", e6.key);
}
