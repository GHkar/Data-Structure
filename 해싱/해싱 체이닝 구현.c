#include<stdio.h>

#define KEY_SIZE 10 //탐색 키의 최대 길이
#define TABLE_SIZE 13 //해시 테이블의 크기 = 소수

typedef struct
{
	char key[KEY_SIZE];
	//다른 필요한 필드들은 여기에 넣는다.
}element;

typedef struct ListNode
{
	element item;
	struct ListNode *link;
}ListNode;
ListNode *hash_table[TABLE_SIZE]; //포인터로 선언해서 주소만 저장

void init_table(element ht[])
{
	int i;
	for (i = 0; i < TABLE_SIZE; i++)
	{
		ht[i].key[0] = NULL; //모든 버켓의 0 인덱스를 NULL 초기화
	}
}

//문자로 된 탐색 키를 숫자로 변환
int transform(char *key)
{
	int number = 0;
	while (*key) // 간단한 덧셈 방식 사용 자연수 생성 + NULL 값을 만날 떄까지 계속 반복
	{
		number += *key++; // key의 모든 값을 더해줌
	}
	return number;
}
//제산 함수를 사용한 해싱 함수
int hash_function(char *key)
{
	return transform(key) % TABLE_SIZE;
}


#define equal(e1, e2)(!strcmp(e1.key, e2.key))

//체이닝을 이용하여 테이블에 키를 삽입
void hash_chain_add(element item, ListNode *ht[])
{
	int hash_value = hash_fuction(item.key);
	ListNode *ptr; //새로운 노드
	ListNode *node_before = NULL; //이전 노드
	ListNode *node = ht[hash_value]; //현재 노드
	for (; node; node_before = node, node = node->link) //노드가 NULL이 아닐 때
	{
		if (equal(node->item, item))
		{
			fprintf(stderr, "이미 탐색 키가 저장되어 있음\n");
			return;
		}
	}
	ptr = (ListNode *)malloc(sizeof(ListNode));
	ptr->item = item;
	ptr->link = NULL;
	if (node_before) //기존의 연결 리스트가 있으면
	{
		node_before->link = ptr;
	}
	else //기존의 연결 리스트가 없으면
	{
		ht[hash_value] = ptr;
	}
}

//체이닝을 이용하여 테이블에 저장된 키를 탐색
void hash_chain_find(element item, ListNode *ht[])
{
	ListNode *node;

	int hash_value = hash_function(item.key);
	for (node = ht[hash_value]; node; node = node->link)
	{
		if (equal(node->item, item))
		{
			printf("키를 찾았음\n");
			return;
		}
	}
	printf("키를 찾지못했음\n");
}

main()
{
	element tmp;
	int op;
	while (1)
	{
		printf("원하는 연산을 입력하시오(0=입력, 1=탐색, 2=종료)=");
		scanf_s("%d", &op);
		if (op == 2) break;
		printf("키를 입력하시오=");
		scanf_s("%s", tmp.key);
		if (op == 0)
		{
			hash_chain_add(tmp, hash_table);
		}
		else if (op == 1)
		{
			hash_chain_search(tmp, hash_table);
		}
	}
}
