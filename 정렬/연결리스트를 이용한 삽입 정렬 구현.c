#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

int n;
typedef int element;
typedef struct ListNode {
	element data;
	struct ListNode *llink;
	struct ListNode *rlink;
}ListNode;

//���� ���� ����Ʈ �ʱ�ȭ
void init(ListNode *phead) {
	phead->llink = phead;
	phead->rlink = phead;
}
//���� �Լ�
void insert_node(ListNode *before, ListNode *new_node) {
	new_node->llink = before;
	new_node->rlink = before->rlink;
	before->rlink->llink = new_node;
	before->rlink = new_node;
}

//���
void dislplay(ListNode *phead) {
	ListNode *p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("%d ", p->data);
	}
	printf("\n");
}

//���� ����
void insertion_sort(ListNode *phead) {
	ListNode *p = phead->rlink;//ù��° ���
	ListNode *c;//���� ���
	ListNode*key; //�ι�° ���
	//��� ����� ���� ��� ���� �Ѱ��� ������ �� ���� ���� ����� ���ؼ� ������ �� �ڸ��� ���� 
	while (1) { 
		key = p->rlink;
		if (key == phead) break;//Ż�� ����
		if (key->data < p->data) { //Ű ���� ���� ����� ������ �۴ٸ� Ű�� ����(�켱 ������ �� ���ٸ�)
			//key ��带 ������
			key->llink->rlink = key->rlink;
			key->rlink->llink = key->llink;
			//
			c = key->llink;//���� �񱳸� ������ ���
			//
			if(c->data > key->data){//���� ���� ���ų� �׺��� ���� ũ�� �̵��� �ʿ�x
				while (c != phead) {//�������� ��� ���ϸ鼭 c�� �̵�
					c = c->llink;
					if (c->data <= key->data) {
						break;
					}
				}
				insert_node(c, key); //������ ��ġ�� ����
			}
		}
		if (p->data <= p->rlink->data) { //���� ����� ���� p����� ������ ������ �̵� ��ų �ʿ�x
			p = p->rlink;
		}
	}
}

void main()
{
	ListNode head_node;
	n = MAX_SIZE;
	ListNode *p[10];
	int i;
	init(&head_node);
	for (i = 0; i < n; i++) {
		p[i] = (ListNode *)malloc(sizeof(ListNode));
		p[i]->data = rand() % n;
		//��� ����� �����ʿ� ����
		insert_node(&head_node, p[i]);
	}
	//���� ��
	dislplay(&head_node);
	printf("\n");
	insertion_sort(&head_node);
	//���� ��
	dislplay(&head_node);
}
