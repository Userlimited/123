#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>

typedef struct tnode
{
	int data;
	struct node *leftchild;
	struct node *rightchild;
}TNODE;

typedef struct node
{
	TNODE *t;
	struct node *next
}NODE;

typedef struct queue
{
	NODE *front;
	NODE *rear;
}QUEUE;
