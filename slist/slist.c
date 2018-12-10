#include <stdio.h>
#include <stdlib.h>

#include "slist.h"

int main()
{
	int arr[10] = { 100, 1, 5, 55, 1001, 2001, 301, 555, 777, 503};
	NODE *root = NULL;
	NODE *search = NULL;
	root = createSList(root, arr, sizeof(arr)/sizeof(arr[0]));
	
	printf("sizeof arr = %ld elem size = %ld\n", sizeof(arr), sizeof(arr[0]));
	
	root = createSList(root, arr, 10);
	printSList(root);
	
	root = insertToSList(root, 445);
	printSList(root);
	
	root = deleteFromSList(root, 2001);
	printSList(root);
	
	search = searchSList(root, 5555);
	if (search)
	{
		printf("%s: Element %d found\n", __FUNCTION__, search->data);
	}
	
	root = revSList(root);
	root = revSListREC(root);
	root = revSListOrder(root, 3);
	
	printf("\n");
	printSList(root);
	printSListREV(root);
	printf("\n");
	printSListREC(root);
	return 1;
}



NODE * createSList(NODE *root, int *arr, int numElem)
{
	NODE *p = NULL, *q = NULL;
	int i = 0;
	if (root)
	{
		printf("List already has elements ... Appending\n");
		p = root;
	}
	for (i = 0; i < numElem; i++)
	{
		p = insertToSList(p, arr[i]);
	}
	return p;
}
NODE * insertToSList(NODE *root, int data)
{
	NODE *p = NULL, *q = NULL, *r = NULL;
	
	CREATE_NODE(root, r, data);
	if(!root)
	{
		return r;
	}

	if (data < root->data)
	{
		r->next = root;
		return r;
	}
	p = q = root;
	while (p)
	{
		if (p->data > data)
		{
			break;
		}
		q = p;
		p = p->next;
	}
	r->next = p;
	q->next = r;
	return root;
}
NODE * deleteFromSList(NODE *root, int data)
{
	NODE *p = NULL, *q = NULL, *r = NULL;
	if(!root)
	{
		return root;	
	}
	if (root->data == data)
	{
		p = root;
		root = root->next;
		free(p);
		return root;
	}
		
	p = q = root;
	while (p)
	{
		if (p->data == data)
		{
			q->next = p->next;
			free(p);
			return root;
		}
		q = p;
		p = p->next;
	}
	printf ("%s : Element not available in slist\n", __FUNCTION__);
	return root;
}
void printSList(NODE *root)
{
	for(; root; root = root->next)
	{
		printf("%d\t", root->data);
	}
	printf("\n");
}
void printSListREV(NODE *root)
{
	if (!root)
	{
		return;
	}
	printSListREV(root->next);
	printf("%d\t", root->data);
}
void printSListREC(NODE *root)
{
	if(!root)
	{
		printf("\n");
		return;
	}
	printf("%d\t", root->data);
	printSListREC(root->next);
}

NODE * searchSList(NODE *root, int data)
{
	NODE *p = NULL, *q = NULL, *r = NULL;
	if (!root)
	{
		printf ("%s : Element %d not available in slist\n", __FUNCTION__, data);
		return NULL;
	}
	p = q = root;
	while(p)
	{
		if(p->data == data)
		{
			return p;
		}
		p = p->next;
	}
	printf ("%s : Element %d not available in slist\n", __FUNCTION__, data);
	return NULL;
}
NODE * searchSListBIN(NODE *root, int data)
{
}

NODE * revSList(NODE *root)
{
	NODE *p = NULL, *q = NULL, *r = NULL;
	p = root;
	if (!root)
	{
		return root;
	}
	while (p)
	{
		q = p->next;
		p->next = r;
		r = p;
		p = q;
	}
	return r;
}

NODE * revSListREC(NODE *root)
{
	NODE *p;
	if (!root || !root->next)
	{
		return root;
	}
	p = revSListREC(root->next);
	root->next->next = root;
	root->next = NULL;
	
	return p;
}
NODE * revSListOrder(NODE *root, int order)
{
	NODE *p = NULL, *q = NULL, *r = NULL;
	p = root;
	q = r = NULL;
	int count = 0;
	
	while(p != NULL && count < order)
	{
		q = p->next;
		p->next = r;
		r = p;
		p = q;
		count++;
	}
	
	if (p)
	{
		root->next = revSListOrder(p, order);
	}
	return r;
}


NODE * revSListOrder1(NODE *root, int n)
{
	NODE *p = root;
	NODE *q,*r;
	int count = 0;
	q = r = NULL;

	while(p!=NULL && count < n)
	{
		q = p->next;
		p->next = r;
		r = p;
		p = q;

		count++;
	}

	if(p != NULL)
		root->next = revSListOrder(p, n);
	return r;
}

NODE * mergeSList(NODE *root1, NODE *root2)
{
}
NODE * findDupInSList(NODE *root)
{
}
NODE * findLoopInSlist(NODE *root)
{
}
NODE * findNthElementFronTail(NODE *root, int n)
{
}

NODE * deleteSlist(NODE *root)
{
}