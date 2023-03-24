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

//이중 연결 리스트 초기화
void init(ListNode *phead) {
	phead->llink = phead;
	phead->rlink = phead;
}
//삽입 함수
void insert_node(ListNode *before, ListNode *new_node) {
	new_node->llink = before;
	new_node->rlink = before->rlink;
	before->rlink->llink = new_node;
	before->rlink = new_node;
}

//출력
void dislplay(ListNode *phead) {
	ListNode *p;
	for (p = phead->rlink; p != phead; p = p->rlink) {
		printf("%d ", p->data);
	}
	printf("\n");
}

//삽입 정렬
void insertion_sort(ListNode *phead) {
	ListNode *p = phead->rlink;//첫번째 노드
	ListNode *c;//비교할 노드
	ListNode*key; //두번째 노드
	//헤드 노드의 다음 노드 값을 넘겨준 다음에 비교 시작 이전 노드들과 비교해서 작으면 그 자리에 삽입 
	while (1) { 
		key = p->rlink;
		if (key == phead) break;//탈출 조건
		if (key->data < p->data) { //키 값이 이전 노드의 값보다 작다면 키를 빼냄(우선 순위가 더 높다면)
			//key 노드를 빼내기
			key->llink->rlink = key->rlink;
			key->rlink->llink = key->llink;
			//
			c = key->llink;//실제 비교를 진행할 노드
			//
			if(c->data > key->data){//이전 노드와 같거나 그보다 값이 크면 이동할 필요x
				while (c != phead) {//왼쪽으로 계속 비교하면서 c를 이동
					c = c->llink;
					if (c->data <= key->data) {
						break;
					}
				}
				insert_node(c, key); //정해진 위치에 삽입
			}
		}
		if (p->data <= p->rlink->data) { //다음 노드의 값이 p노드의 값보다 작으면 이동 시킬 필요x
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
		//헤드 노드의 오른쪽에 삽입
		insert_node(&head_node, p[i]);
	}
	//정렬 전
	dislplay(&head_node);
	printf("\n");
	insertion_sort(&head_node);
	//정렬 후
	dislplay(&head_node);
}
