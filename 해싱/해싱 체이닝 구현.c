#include<stdio.h>

#define KEY_SIZE 10 //Ž�� Ű�� �ִ� ����
#define TABLE_SIZE 13 //�ؽ� ���̺��� ũ�� = �Ҽ�

typedef struct
{
	char key[KEY_SIZE];
	//�ٸ� �ʿ��� �ʵ���� ���⿡ �ִ´�.
}element;

typedef struct ListNode
{
	element item;
	struct ListNode *link;
}ListNode;
ListNode *hash_table[TABLE_SIZE]; //�����ͷ� �����ؼ� �ּҸ� ����

void init_table(element ht[])
{
	int i;
	for (i = 0; i < TABLE_SIZE; i++)
	{
		ht[i].key[0] = NULL; //��� ������ 0 �ε����� NULL �ʱ�ȭ
	}
}

//���ڷ� �� Ž�� Ű�� ���ڷ� ��ȯ
int transform(char *key)
{
	int number = 0;
	while (*key) // ������ ���� ��� ��� �ڿ��� ���� + NULL ���� ���� ������ ��� �ݺ�
	{
		number += *key++; // key�� ��� ���� ������
	}
	return number;
}
//���� �Լ��� ����� �ؽ� �Լ�
int hash_function(char *key)
{
	return transform(key) % TABLE_SIZE;
}


#define equal(e1, e2)(!strcmp(e1.key, e2.key))

//ü�̴��� �̿��Ͽ� ���̺� Ű�� ����
void hash_chain_add(element item, ListNode *ht[])
{
	int hash_value = hash_fuction(item.key);
	ListNode *ptr; //���ο� ���
	ListNode *node_before = NULL; //���� ���
	ListNode *node = ht[hash_value]; //���� ���
	for (; node; node_before = node, node = node->link) //��尡 NULL�� �ƴ� ��
	{
		if (equal(node->item, item))
		{
			fprintf(stderr, "�̹� Ž�� Ű�� ����Ǿ� ����\n");
			return;
		}
	}
	ptr = (ListNode *)malloc(sizeof(ListNode));
	ptr->item = item;
	ptr->link = NULL;
	if (node_before) //������ ���� ����Ʈ�� ������
	{
		node_before->link = ptr;
	}
	else //������ ���� ����Ʈ�� ������
	{
		ht[hash_value] = ptr;
	}
}

//ü�̴��� �̿��Ͽ� ���̺� ����� Ű�� Ž��
void hash_chain_find(element item, ListNode *ht[])
{
	ListNode *node;

	int hash_value = hash_function(item.key);
	for (node = ht[hash_value]; node; node = node->link)
	{
		if (equal(node->item, item))
		{
			printf("Ű�� ã����\n");
			return;
		}
	}
	printf("Ű�� ã��������\n");
}

main()
{
	element tmp;
	int op;
	while (1)
	{
		printf("���ϴ� ������ �Է��Ͻÿ�(0=�Է�, 1=Ž��, 2=����)=");
		scanf_s("%d", &op);
		if (op == 2) break;
		printf("Ű�� �Է��Ͻÿ�=");
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
