#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_item{
	void *data;
	struct stack_item *prev;
} stack_item;

typedef struct{
	stack_item *this;
} stack;

stack *stack_new()
{
	stack *ptr = malloc(sizeof(stack));
	if (ptr != NULL){
		ptr->this = NULL;
	}
	return ptr;
}

int stack_push(stack *stk, void *data)
{
	stack_item *item = malloc(sizeof(stack_item));
	if (item == NULL){
		return 0;
	}
	item->prev = stk->this;
	item->data = data;
	stk->this = item;
	return 1;
}

void *stack_pull(stack *stk)
{
	if (stk->this == NULL){
		return NULL;
	}
	stack_item *prev = stk->this->prev;
	void *data = stk->this->data;
	free(stk->this);
	stk->this = prev;
	return data;
}

int main()
{
	int n1 = 5;
	int n2 = 6;
	
	stack *stk = stack_new();
	stack_push(stk, &n1);
	stack_push(stk, &n2);
	
	int elem = *(int*)stack_pull(stk);
	printf("%d\n", elem);
	elem = *(int*)stack_pull(stk);
	printf("%d\n", elem);
	
	/*
	6
	5
	*/
	
	return 0;
}
