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
	ListNode *head;     // ��� ������
	int length;     // ����� ����
} ListType;

// phead: ����Ʈ�� ��� �������� ������
// p : ���� ���
// new_node : ���Ե� ���
void insert_node(ListNode **phead, ListNode *p,
	ListNode *new_node)
{
	if (*phead == NULL) {   // ���鸮��Ʈ�� ���
		new_node->link = NULL;
		*phead = new_node;
	}
	else if (p == NULL) { // p�� NULL�̸� ù��° ���� ����
		new_node->link = *phead;
		*phead = new_node;
	}
	else {           // p ������ ����
		new_node->link = p->link;
		p->link = new_node;
	}
}
// ����Ʈ�� �ʱ�ȭ�Ѵ�.
void init(ListType *list)
{
	if (list == NULL) return;
	list->length = 0;
	list->head = NULL;
}
// ����Ʈ�ȿ��� pos ��ġ�� ��带 ��ȯ�Ѵ�.
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
// ����Ʈ�� �׸��� ������ ��ȯ�Ѵ�.
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
// �־��� ��ġ�� �����͸� ���ĵ� ���·� �����Ѵ�.
void add_ascending(ListType *list, element data)
{

	ListNode *p;

	ListNode*node = (ListNode *)malloc(sizeof(ListNode));
	if (node == NULL) error("�޸� �Ҵ翡��");
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
// ������ ������ ����Ѵ�.
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
		printf("���ڸ� �Է��ϼ���: ");
		scanf_s("%d", &data);
		if (data == -1) {
			break;
		}
		add_ascending(&list1, data);
		display(&list1);
	}
}
