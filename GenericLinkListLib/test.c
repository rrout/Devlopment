#include <stdio.h>
#include <stdlib.h>
#include "genericlist.h"
LIST slist;

int main()
{
	int arr[10] = {11, 12, 13, 20, 30, 111, 987, 567, 876, 8796};
	int i, *aa;
	GLITER iter;
	int *x = malloc(sizeof(int));
	*x = 55;
	gListInit(&slist, "G-SLIST");

	for (i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
	{
		gListAddElem(&slist, &arr[i]);
	}
	gListShow(&slist);

	gListAddElem(&slist, x);
	gListRemoveElem(&slist, &arr[0]);
	gListRemoveElem(&slist, &arr[5]);
	gListShow(&slist);

	i = 0;
	for(aa = gLiistIterInit(&slist, &iter); aa;
		aa = gLiistIterNext(&slist, &iter))
	{
		printf("Elem(%d) = %d\n", i++, *aa);
	}
	printf("\n");
	i = 0;
	for(aa = gLiistIterInit(&slist, &iter); aa;
		aa = gLiistIterNext(&slist, &iter))
	{
		if (*aa == 30)
		{
			gLiistIterRemove(&slist, &iter);
			continue;
		}
		printf("Elem(%d) = %d\n", i++, *aa);
	}

	printf("\n");
	i = 0;
	for(aa = gLiistIterInit(&slist, &iter); aa;
		aa = gLiistIterNext(&slist, &iter))
	{
		printf("Elem(%d) = %d\n", i++, *aa);
	}
	gListShow(&slist);
	return 1;
}