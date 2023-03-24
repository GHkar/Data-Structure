#include<stdio.h>
#define MAX_ELEMENT 200

typedef struct {
	int key;
}element;
typedef struct {
	element heap[MAX_ELEMENT];
	int heap_size;
}HeapType;


//�ʱ�ȭ �Լ�
init(HeapType *h)
{
	h->heap_size = 0;
}
//���� �Լ�
void insert_max_heap(HeapType *h, element item)
{
	int i;
	i = ++(h->heap_size);

	//Ʈ���� �Ž��� �ö󰡸鼭 �θ� ���� ���ϴ� ����
	while ((i != 1) && (item.key > h->heap[i / 2].key)) {
		h->heap[i] = h->heap[i / 2];
		i /= 2;
	}
	h->heap[i] = item;	//���ο� ��带 ���� 
}
//���� �Լ�
element delete_max_heap(HeapType *h)
{
	int parent, child;
	element item, temp;

	item = h->heap[1]; //������ �� + ������ ��
	temp = h->heap[(h->heap_size)--];
	parent = 1;
	child = 2;
	while (child <= h->heap_size) {
		//���� ����� �ڽ� ��� �� �� ���� �ڽ� ��带 ã�´�.
		if ((child < h->heap_size) &&
			(h->heap[child].key) < h->heap[child + 1].key)
			child++;
		if (temp.key >= h->heap[child].key) break;
		// �Ѵܰ� �Ʒ��� �̵�
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}
//�켱���� ť�� ������ �̿��� ����
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
//���Լ�
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
