#include<stdio.h>
#include<stdlib.h>
#define INPUT_FILE		"input.txt"

#define MAX_NAME_SIZE	10
#define MAX_PHONE_SIZE	11
#define MAX_CONTACT_NUM	10
#define MAX_HASH_MODE	3
#define FILTER_SIZE		31251	

typedef struct contact {
	char	phone[MAX_PHONE_SIZE+1];
	char	name[MAX_NAME_SIZE];
} contact_t;
contact_t	contacts[MAX_CONTACT_NUM];

int bloom_filter[FILTER_SIZE];	/* 32*31251 */
int input_count = 0;

void print_array() 
{
	int i;
	printf("*연락처(%d)\n", input_count);
	for (i=0; i<input_count; i++) {
		printf("%s:\t%s\n", contacts[i].phone, contacts[i].name);
	}
	printf("================================\n");
}
int init_array() 
{
	int i = 0;
	FILE *fp;
	if((fp = fopen(INPUT_FILE, "r")) == NULL) {
		printf("파일을 열지 못했습니다(file=%s)\n", INPUT_FILE); 
		return -1;
	}	
	while(fscanf(fp, "%s %s", contacts[input_count].phone, &contacts[input_count].name) != EOF) {
		input_count++;
		if (input_count>=MAX_CONTACT_NUM) {
			printf("배열에 빈 공간이 없습니다(MAX_CONTACT_NUM=%d)\n", MAX_CONTACT_NUM);
			return -1;
		}
	}	
	return 0;
}
/* Hashing 결과에 따라 bloom filter 설정 */ 
void set_hash(int hash_value[])
{
	int i;
	int array_pos, bit_pos;
	for (i=0; i<MAX_HASH_MODE; i++) {
		array_pos = hash_value[i] / (sizeof(int)*8);
		bit_pos = hash_value[i] % (sizeof(int)*8);
		bloom_filter[array_pos] = bloom_filter[array_pos] | (1<<bit_pos);
		printf("%d %d\n", array_pos, bit_pos);
	}
}
void get_hash(char *key, int hash_value[])
{	
	int i = 1;
	/* 01023640610 중 010은 제외 */ 
	key = key + 3;
	while(*key) {
		hash_value[0] = hash_value[0] + (*key-'0');
		hash_value[1] = hash_value[1] + ((*key-'0')*i);
		hash_value[2] = hash_value[2] + ((*key-'0')<<i);
		key++;
		i++;
	}
}
void set_bloom() 
{
	int i, j;
	printf("*해시 결과\n");
	for (i=0; i<input_count; i++) {
		int hash_value[MAX_HASH_MODE] = {0};
		get_hash(contacts[i].phone, hash_value);
		printf("%s:%5d %5d %5d\n", 
			contacts[i].phone, hash_value[0], 
			hash_value[1], hash_value[2]);
		set_hash(hash_value);
	}
	printf("================================\n");
}

void serch_bloom()
{
	char inputPhoneNum[20];
	printf("*검색\n");
	printf("프로그램을 종료하고 싶다면 stop 을 입력\n");  
	while(1)
	{
		int i;
		printf("핸드폰 번호를 입력하세요 :");
		gets(inputPhoneNum);
		
		
		
		if(strcmp(inputPhoneNum, "stop") == 0)
		{
			printf("프로그램을 종료합니다...");
			break;
		}
		
		int hash_valueN[MAX_HASH_MODE] = {0};
		get_hash(inputPhoneNum, hash_valueN);
//		printf("%s:%5d %5d %5d\n", 
//			inputPhoneNum, hash_valueN[0], 
//			hash_valueN[1], hash_valueN[2]);
		int array_pos, bit_pos;
		int true[3];
		printf("*검색결과\n");
		for (i=0; i<3; i++) {
			
			array_pos = hash_valueN[i] / (sizeof(int)*8);
			bit_pos = hash_valueN[i] % (sizeof(int)*8);
			if(bloom_filter[array_pos] && (1<<bit_pos))
			{
				true[i] = 1;
			}
			else
			{
				true[i] = 0;
			}
		}
		if(true[0] + true[1] + true[2] == 3)
		{
			printf("FOUND\n");
		}
		else
		{
			printf("NOT FOUND\n");
		}
	}
	
	
}
int main()
{
	int res;
	res = init_array();
	if (res < 0) {
		printf("파일을 열지 못했습니다.\n");
		return -1; 
	}
	print_array();
	set_bloom();
	serch_bloom();
	return 0;
}
