#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MAXSIZE 10

void swap(int *a, int *b)
{
	int p = *a;
	*a = *b;
	*b = p;
}

void array_init(int array[], int j)
{
	int i;
	srand(time(NULL));
	for (i = 0; i < j; i++)
	{
		array[i] = rand()%(j*2);
	}
}

int getpostion(int *array, int i, int j)
{
	int key = array[i];

	while(i != j)
	{
		while(array[j] >= key && i != j)
		{
			j--;
		}
		swap(&array[i], &array[j]);
		while(array[i] < key && i != j)
		{
			i++;
		}
		swap(&array[i], &array[j]);
	}
	return i;
}

void display(int array[], int j)
{
	int i;
	for (i = 0; i < j-1; i++)
	{
		printf("%d ", array[i]);
	}
	printf("%d\n", array[j-1]);
}

void quick_sort(int *a, int i, int j)
{
	if (i >= j)
	{
		return;	
	}

	int mid = getpostion(a, i, j);
	quick_sort(a, i, mid-1);
	quick_sort(a, mid+1, j);
}
	
int main()
{
	srand(time(NULL));
	int array[MAXSIZE];
	array_init(array, MAXSIZE);
	display(array, MAXSIZE);
	getpostion(array, 0, MAXSIZE-1);
	display(array, MAXSIZE);
	quick_sort(array,0,MAXSIZE-1);
	display(array, MAXSIZE);
	return 0;
}
