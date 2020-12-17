#include <stdio.h>
#define SIZE 10

void bubblesort(int *array, const int size)
{
	int pass, j;
	for (pass = 0; pass < size - 1; pass++)
	{
		for (j = 0; j < size - 1; j++)
		{
			if (array[j] > array[j + 1])
			{
				swap(&array[j], &array[j + 1]);
			}
		}
	}
}

void swap(int *ptr1, int *ptr2)
{
	int hold = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = hold;
}

int main(void)
{
	int i;
/*	int a[SIZE] = {2, 6, 4, 8, 10, 12, 89, 68, 42, 37}; */

	int *a;

/* 	a = calloc(10, sizeof(*a)); */
	a = malloc(10 * sizeof(*a));

/* 	a[0] = 2;
	a[1] = 6;
	a[2] = 4;
	a[3] = 8;
	a[4] = 10;
	a[5] = 12;
	a[6] = 89;
	a[7] = 68;
	a[8] = 42;
//	a[9] = 37; */


	printf("Data items in original order\n");

	for (i = 0; i < SIZE; i++)
	{
		printf("%4d", a[i]);
	}

	printf("\n");

	bubblesort(a, SIZE);

	printf("Data items in ascending order\n");

	for (i = 0; i < SIZE; i++)
	{
		printf("%4d", a[i]);
	}

	printf("\n");

	return 0;
}
