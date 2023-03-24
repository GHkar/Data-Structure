#include<stdio.h>
#include<string.h>

#define KEY_SIZE 10 //Ž�� Ű�� �ִ� ����
#define TABLE_SIZE 13 //�ؽ� ���̺��� ũ�� = �Ҽ�


typedef struct
{
	int id;
	char name[100];
	char gender[100];
	char city[100];
}DB;

DB DataBase[5] = {
	{ 200030, "Alice", "F", "Daegu"},
	{ 200050, "Bob", "M","Daegu"},
	{ 200063, "Bell", "M","Inchon"},
	{ 200067, "Charlie","M", "Seoul"},
	{ 200071, "Diana", "F","Seoul"} };


int hash_table_id[TABLE_SIZE]; //�ؽ� ���̺�
int hash_table_name[TABLE_SIZE]; //�ؽ� ���̺�

void init_table(int ht[])
{
	int i;
	for (i = 0; i < TABLE_SIZE; i++)
	{
		ht[i] = -1;
	}
}


//���� �Լ��� ����� �ؽ� �Լ�
int name_hash(char *key)
{
	int number = 0;
	while (*key)
	{
		number += *key++;
	}
	//printf("%d", number);
	return number % TABLE_SIZE;
}

int id_hash(int key)
{
	int two = key % 200000;
	return two % TABLE_SIZE;
}

#define empty(e) (strlen(e) == 0) //���̰� 0�̸�
#define equal(e1, e2) (!strcmp(e1, e2))

//���� ������� �̿��Ͽ� ���̺� Ű�� �����ϰ�,
//���̺��� ���� �� ���� ����
void hash_lp_add()
{
	int i, j, hash_value;


	for (i = 0; i < 5; i++)
	{
		hash_value = id_hash(DataBase[i].id); // �ε�����
		for (j = 0; j < 5; j++)
		{
			if (hash_table_id[hash_value] == j)
			{
				hash_value = (++hash_value) % TABLE_SIZE; // +1�� �ϴ� ������ ����Ž���̶�, �� ���� �ε����� �߰��ؾ��ϱ� ����
			}
		}
		hash_table_id[hash_value] = i;
	}

	for (i = 0; i < 5; i++)
	{
		hash_value = name_hash(DataBase[i].name); // �ε�����
												  //printf("%d", hash_value);
		for (j = 0; j < 5; j++)
		{
			if (hash_table_name[hash_value] == j)
			{
				hash_value = (hash_value++) % TABLE_SIZE; // +1�� �ϴ� ������ ����Ž���̶�, �� ���� �ε����� �߰��ؾ��ϱ� ����
			}
		}
		hash_table_name[hash_value] = i;
	}
}

//���� ������� �̿��Ͽ� ���̺� ����� Ű�� Ž��
void hash_lp_search_id(int item)
{
	int i, index, hash_value;

	hash_value = id_hash(item);
	//printf("%d", hash_value);

	if (hash_table_id[hash_value] != -1)
	{
		index = hash_table_id[hash_value];
		if (DataBase[index].id == item)
		{
			printf("%d, %s, %s, %s \n", DataBase[index].id, DataBase[index].name, DataBase[index].gender, DataBase[index].city);
		}
		else
		{
			printf("�׷� ����ڴ� �����ϴ�.\n");
		}
	}
	else
	{
		printf("�׷� ����ڴ� �����ϴ�.\n");
	}

}

void hash_lp_search_name(char *item)
{
	int i, index, hash_value;
	hash_value = name_hash(item);

	if (hash_table_name[hash_value] != -1)
	{
		index = hash_table_name[hash_value];
		if (equal(DataBase[index].name, item))
		{
			printf("%d, %s, %s, %s \n", DataBase[index].id, DataBase[index].name, DataBase[index].gender, DataBase[index].city);
		}
		else
		{
			printf("�׷� ����ڴ� �����ϴ�.\n");
		}
	}
	else
	{
		printf("�׷� ����ڴ� �����ϴ�.\n");
	}

}

//�ؽ� ���̺��� ������ ���
void hash_lp_print(int ht[])
{
	int i;
	for (i = 0; i < TABLE_SIZE; i++)
	{
		printf("[%d]		%d\n", i, ht[i]);
	}
}

void hash_lp_print_DB()
{
	int index;
	for (index = 0; index < 5; index++)
	{
		printf("%d, %s, %s, %s \n", DataBase[index].id, DataBase[index].name, DataBase[index].gender, DataBase[index].city);
	}
}
//�ؽ� ���̺��� ����� ����
main()
{

	init_table(hash_table_id);
	init_table(hash_table_name);

	



	//�ؽ� ���̺� ����
	hash_lp_add();
	char tmp[100];
	int tmpp;
	int op;
	hash_lp_print_DB();
	printf("=========================================\n");
	hash_lp_print(hash_table_id);
	printf("=========================================\n");
	hash_lp_print(hash_table_name);

	while (1)
	{
		printf("���ϴ� ������ �Է��Ͻÿ�(1=ID Ž��, 2=Name Ž�� 3=����)= ");
		scanf_s("%d", &op);
		if (op == 3) break;

		else if (op == 1)
		{
			printf("ID�� �Է��Ͻÿ�= ");
			scanf_s("%d", &tmpp);
			hash_lp_search_id(tmpp);
		}
		else if (op == 2)
		{
			printf("Name�� �Է��Ͻÿ�= ");
			scanf_s("%s", tmp);

			hash_lp_search_name(tmp);
		}
	}
}
