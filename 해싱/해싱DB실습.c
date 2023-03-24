#include<stdio.h>
#include<string.h>

#define KEY_SIZE 10 //탐색 키의 최대 길이
#define TABLE_SIZE 13 //해시 테이블의 크기 = 소수


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


int hash_table_id[TABLE_SIZE]; //해시 테이블
int hash_table_name[TABLE_SIZE]; //해시 테이블

void init_table(int ht[])
{
	int i;
	for (i = 0; i < TABLE_SIZE; i++)
	{
		ht[i] = -1;
	}
}


//제산 함수를 사용한 해싱 함수
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

#define empty(e) (strlen(e) == 0) //길이가 0이면
#define equal(e1, e2) (!strcmp(e1, e2))

//선형 조사법을 이용하여 테이블에 키를 삽입하고,
//테이블이 가득 찬 경우는 종료
void hash_lp_add()
{
	int i, j, hash_value;


	for (i = 0; i < 5; i++)
	{
		hash_value = id_hash(DataBase[i].id); // 인덱스값
		for (j = 0; j < 5; j++)
		{
			if (hash_table_id[hash_value] == j)
			{
				hash_value = (++hash_value) % TABLE_SIZE; // +1을 하는 이유는 선형탐색이라서, 즉 다음 인덱스에 추가해야하기 때문
			}
		}
		hash_table_id[hash_value] = i;
	}

	for (i = 0; i < 5; i++)
	{
		hash_value = name_hash(DataBase[i].name); // 인덱스값
												  //printf("%d", hash_value);
		for (j = 0; j < 5; j++)
		{
			if (hash_table_name[hash_value] == j)
			{
				hash_value = (hash_value++) % TABLE_SIZE; // +1을 하는 이유는 선형탐색이라서, 즉 다음 인덱스에 추가해야하기 때문
			}
		}
		hash_table_name[hash_value] = i;
	}
}

//선형 조사법을 이용하여 테이블에 저장된 키를 탐색
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
			printf("그런 사용자는 없습니다.\n");
		}
	}
	else
	{
		printf("그런 사용자는 없습니다.\n");
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
			printf("그런 사용자는 없습니다.\n");
		}
	}
	else
	{
		printf("그런 사용자는 없습니다.\n");
	}

}

//해싱 테이블의 내용을 출력
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
//해싱 테이블을 사용한 예제
main()
{

	init_table(hash_table_id);
	init_table(hash_table_name);

	



	//해쉬 테이블 생성
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
		printf("원하는 연산을 입력하시오(1=ID 탐색, 2=Name 탐색 3=종료)= ");
		scanf_s("%d", &op);
		if (op == 3) break;

		else if (op == 1)
		{
			printf("ID를 입력하시오= ");
			scanf_s("%d", &tmpp);
			hash_lp_search_id(tmpp);
		}
		else if (op == 2)
		{
			printf("Name을 입력하시오= ");
			scanf_s("%s", tmp);

			hash_lp_search_name(tmp);
		}
	}
}
