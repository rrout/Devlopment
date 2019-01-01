#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

int main()
{
	int arr[10] = {11, 12, 13, 20, 30, 111, 987, 567, 876, 8796};
	int i, *aa;
	bst_t *treeRoot = NULL;

	for (i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
	{
		treeRoot = insertBstNode(treeRoot, arr[i]);
	}
	printBstGraph(treeRoot, 2);
	i = getBstHeight(treeRoot);
	printf("Height : %d\n", i);
	i = getBstLeafCount(treeRoot);
	printf("Leaf count : %d\n", i);
	i = getBstNodeCount(treeRoot);
	printf("Node count : %d\n", i);
	return 1;
}
