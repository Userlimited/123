#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
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
	
void merge(int *a, int i, int mid, int j)
{
	int astart = i;
	int bstart = mid + 1;
	int *p = (int *)malloc(4*(j-i+1));
	int *q = p;

	while(astart <= mid && bstart <= j)
	{
		if (a[astart] < a[bstart])
		{
			*p = a[astart];
			p++;
			astart++;
		}
		else
		{
			*p = a[bstart];
			p++;
			bstart++;
		}
	}

	while(astart <= mid)
	{
		*p = a[astart];
		p++;
		astart++;
	}
	
	while(bstart <= j)
	{
		*p = a[bstart];
		p++;
		bstart++;
	}

	memcpy(a+i, q, 4*(j-i+1));
	free(q);
}

void mergesort(int *a, int i, int j)
{
	int mid = (i+j)/2;
	if (i >= j)
	{
		return;
	}

	mergesort(a, i, mid);
	mergesort(a, mid+1, j);
	merge(a, i, mid, j);
}

int main()
{
	int a[MAXSIZE];
	array_init(a, MAXSIZE);
	display(a, MAXSIZE);
	mergesort(a, 0, MAXSIZE-1);
	display(a, MAXSIZE);
}
