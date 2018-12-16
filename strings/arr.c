#include <stdio.h>

int binarySearchArray(int *arr, int start, int end, int data)
{
	int  mid = 0;
	if (start >= end)
		return -1;
	mid = (start+ end)/2;
	if (arr[mid] == data)
		return mid;
	else if (arr[mid] < data)
		start = mid +1;
	else (arr[mid] > data)
		end = mid -1;
	index = binarySearchArray(arr,start, end, data);
	return index;
}

int binarySearchArray(int *arr, int size, int data)
{
	int start = 0, end = size, mid = 0;
	while(start <= end)
	{
		mid = (start+ end)/2;
		if (arr[mid] == data)
			return mid;
		else if (arr[mid] < data)
			start = mid + 1;
		else
			end = mid -1;
	}
	return -1;
}

