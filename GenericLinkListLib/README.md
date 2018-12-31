--------- Generic Linked List -----------
How To Use

1. Create a List Base
		LIST slist;  slist is the List Base
2. malloc list element
	it can be if any type
3. Add to list using gListAddElem
	gListAddElem(&slist, x);
4. Browse
	for(aa = gLiistIterInit(&slist, &iter); aa;
		aa = gLiistIterNext(&slist, &iter))
	{
		printf("Elem(%d) = %d\n", i++, *aa);
	}
5. display using gListShow(&slist);
