#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct node
{
	int data;
	struct node *next;
}node_t;

typedef struct stack
{
	node_t *top;
}stack_t;

stack_t *stack_init(void)
{
	stack_t *stack = (stack_t *)malloc(sizeof(stack_t));
	assert(stack != NULL);

	stack->top = NULL;
	return stack;
}

int stack_empty(stack_t *stack)
{
	if (stack->top == NULL)
	{
		return 1;
	}

	return 0;
}

void push(stack_t *stack, int data)
{
	node_t *pnew = (node_t *)malloc(sizeof(node_t));
	assert(pnew != NULL);

	pnew->data = data;
	pnew->next = stack->top;
	stack->top = pnew;
}

void pop(stack_t *stack)
{
	node_t *p = stack->top;
	if (stack_empty(stack))
	{
		return;
	}
	stack->top = p->next;
	free(p);
}

void display_stack(stack_t *stack)
{
	node_t *p = stack->top;

	while(p)
	{
		printf("%d\n", p->data);
		p = p->next;
	}

}

int top(stack_t *stack)
{
	if(stack_empty(stack))
	{
		return -1;
	}
	return stack->top->data;
}

void stack_clear(stack_t *stack)
{
	while(stack_empty(stack) != 1)
	{
		pop(stack);
	}
}

void stack_destroy(stack_t **stack)
{
	stack_clear(*stack);
	free(*stack);
	*stack = NULL;
}

int isLeftK(int ch)
{
	if (ch == '(' || ch == '[')
	{
		return 1;
	}
	return 0;
}

int isRightK(int ch)
{
	if (ch == ')' || ch == ']')
	{
		return 1;
	}
	return 0;
}

int isRight(int temp, int p)
{
	if(temp == '(' && p == ')' || temp == '[' && p == ']')
	{
		return 1;
	}
	return 0;
}

int main()
{
/*
	stack_t *stack = stack_init();
	push(stack,1);
	push(stack,2);
	push(stack,3);
	push(stack,4);
	pop(stack);
	display_stack(stack);
*/
	char buf[30] = {0};
	fgets(buf, 30, stdin);
	stack_t *stack = stack_init();
	char *p = buf;
	int temp;

	while(*p != '\0')
	{
		if (isLeftK(*p) == 1)
		{
			push(stack, *p);
		}
		else if (isRightK(*p) == 1)
		{
			temp = top(stack);
			if (isRight(temp,*p) == 1)
			{
				pop(stack);
			}
			else
			{
				printf("error\n");
				return 0;
			}
		}
		p++;
	}

	if (stack_empty(stack) == 1)
	{
		printf("success\n");
	}
	else
	{
		printf("error\n");
	}
	return 0;
}

