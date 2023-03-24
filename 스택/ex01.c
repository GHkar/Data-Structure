#include <stdio.h>

#include <string.h>

#include <stdlib.h>

 

#define MAX_STACK_SIZE 100

#define MAZE_SIZE 6

 

 

typedef struct {

	short r;

	short c;

} element;

 

typedef struct {

	element stack[MAX_STACK_SIZE];

	int top;

}StackType;

 

 

 

 

//스택 초기화 함수

void init(StackType *s)

{

	s->top = -1;

}

//공백 상태 검출 함수

int is_empty(StackType *s)

{

	return (s->top == -1);

}

//포화 상태 검출 함수

int is_full(StackType *s)

{

	return (s->top == (MAX_STACK_SIZE - 1));

}

//삽입 함수

void push(StackType *s, element item)

{

	if (is_full(s)) {

		fprintf(stderr, "스택 포화 에러\n");

		return;

	}

	else s->stack[++(s->top)] = item;

}

//삭제 함수

element pop(StackType *s)

{

	if (is_empty(s)) {

		fprintf(stderr, "스택 공백 에러\n");

		exit(1);

	}

	else return s->stack[(s->top)--];

}

 

 

 

element here = { 1,0 }, entry = { 1,0 };

 

char maze[MAZE_SIZE][MAZE_SIZE] = {

	{'1', '1', '1', '1', '1', '1'},

	{'e', '0', '0', '0', '0', '1'},

	{'1', '0', '1', '0', '1', '1'},

	{'1', '1', '1', '0', '0', 'x'},

	{'1', '1', '1', '0', '1', '1'},

	{'1', '1', '1', '1', '1', '1'},

};

 

void push_loc(StackType *s, int r, int c)

{

	if (r < 0 || c < 0) return;

	if (maze[r][c] != '1' && maze[r][c] != '.') {

		element tmp;

		tmp.r = r;

		tmp.c = c;

		push(s, tmp);

	}

}

 

int main()

{

	int r, c;

	StackType s;

	StackType replay;

 

 

	init(&s);

	here = entry;

	while (maze[here.r][here.c] != 'x') {

		r = here.r;

		c = here.c;

		maze[r][c] = '.';

		push_loc(&s, r - 1, c);

		push_loc(&s, r + 1, c);

		push_loc(&s, r, c-1);

		push_loc(&s, r, c+1);

		if (is_empty(&s)) {

			printf("실패\n");

			return -1;

		}

		else

			here = pop(&s);

			printf("(%d, %d)\n", here.r, here.c);

	

	}

	printf("성공\n");

	return 0;

}
