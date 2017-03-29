#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXSIZE 10

void array_init(int a[],int j)
{
	int i;	
	for (i = 0; i < j; i++)
	{
		*(a+i) = rand()%(2*j);
	}
} 

void display(int a[],int j)
{
	
	int i;	
	for (i = 0; i < j; i++)
	{
		printf("%d ", *(a+i));
	}
	printf("\n");
}

int main()
{
	srand(time(NULL));
	int i;
	int a[10];
//	for (i = 0; i < 10; i++)
//	{
//		a[i] = rand()%20;
//	}
	array_init(a,MAXSIZE);
/*	for (i = 0; i < 9; i++)
	{
		printf("%d ",a[i]);
	}
	printf("%d\n", a[9]);
*/
	display(a,MAXSIZE);
}
