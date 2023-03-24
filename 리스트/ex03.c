#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <limits.h>

#define FALSE 0
#define TRUE 1

typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode *link;
} ListNode;
typedef struct {
	ListNode *head;     // 헤드 포인터
	int length;     // 노드의 개수
} ListType;

// phead: 리스트의 헤드 포인터의 포인터
// p : 선행 노드
// new_node : 삽입될 노드
void insert_node(ListNode **phead, ListNode *p,
	ListNode *new_node)
{
	if (*phead == NULL) {   // 공백리스트인 경우
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) { // p가 NULL이면 첫번째 노드로 삽입
		new_node->link = *phead;
		*phead = new_node;
	}
	else {           // p 다음에 삽입
		new_node->link = p->link;
		p->link = new_node;
	}
}
// 리스트를 초기화한다.
void init(ListType *list)
{
	if (list == NULL) return;
	list->length = 0;
	list->head = NULL;
}
// 리스트안에서 pos 위치의 노드를 반환한다.
ListNode *get_node_at_ascending(ListType *list, element data)
{

	ListNode *pre = NULL;
	ListNode *tmp_node = list->head;
	int i;

	if (list->length == 0)
		return NULL;
	for (i = 0; i < list->length; i++)
	{
		if (tmp_node->data < data)
		{
			pre = tmp_node;
			tmp_node = tmp_node->link;
		}

	}
	return pre;

}
// 리스트의 항목의 개수를 반환한다.
int get_length(ListType *list)
{
	return list->length;
}
//
void error(char *message)
{
	fprintf(stderr, "%s\n", message);
	exit(1);
}
// 주어진 위치에 데이터를 정렬된 형태로 삽입한다.
void add_ascending(ListType *list, element data)
{

	ListNode *p;

	ListNode*node = (ListNode *)malloc(sizeof(ListNode));
	if (node == NULL) error("메모리 할당에러");
	node->data = data;
	p = get_node_at_ascending(list, data);

	insert_node(&(list->head), p, node);
	list->length++;

}
//
int is_empty(ListType *list)
{
	if (list->head == NULL) return 1;
	else return 0;
}
// 버퍼의 내용을 출력한다.
void display(ListType *list)
{
	int i;
	ListNode *node = list->head;
	printf("( ");
	for (i = 0;i<list->length;i++) {
		printf("%d ", node->data);
		node = node->link;
	}
	printf(" )\n");
}
//
int main()
{
	ListType list1;
	init(&list1);
	int data = 0;
	while (1) {
		printf("숫자를 입력하세요: ");
		scanf_s("%d", &data);
		if (data == -1) {
			break;
		}
		add_ascending(&list1, data);
		display(&list1);
	}
}
