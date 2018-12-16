#include <stdio.h>
#include <stdlib.h>


int pow(int num, int pow)
{
	if (pow == 1)
		return num;
	return num * pow(num, pow-1);
}

int seriesREC(int pos)
{
	if (pos == 0 || pos ==1)
		return 1;
	return seriesREC(pos) + seriesREC(pos-1);
}

int series(int pos)
{
	int a = 0, b = 0, c = 0;
	if (pos == 0 || pos ==1)
	{
		a = 1;
		b = 1;
		c = 1;
	}

	for (i = 2; i <= pos; i++)
	{
		c = a + b;
		a = b;
		b = c;
	}
	return c;
}

#define NUM_ROW 5
#define NUM_COL 5

int ** alloc2DArray(int row, int col)
{
	for i = 0;
	int **p = malloc(sizeof(int *) * row);
	for (i = 0; i< row ; i++)
	{
		p[i] = mallpc (sizeof(int) * col);
	}
	rteurn p;
}



