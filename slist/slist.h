#include <stdio.h>

typedef struct _node{
	int data;
	struct _node *next;
}NODE;

#define CREATE_NODE(root, ptr, data) \
		ptr = (NODE *) malloc(sizeof(NODE)); \
		if (ptr) { \
			ptr->data = data; \
			ptr->next = NULL; \
		}\
		else {\
			return root;\
		} \
NODE * createSList(NODE *root, int *arr, int numElem);
NODE * createSList(NODE *root, int *arr, int numElem);
NODE * insertToSList(NODE *root, int data);
NODE * deleteFromSList(NODE *root, int data);
void printSList(NODE *root);
void printSListREV(NODE *root);
void printSListREC(NODE *root);

NODE * searchSList(NODE *root, int data);
NODE * searchSListBIN(NODE *root, int data);

NODE * revSList(NODE *root);
NODE * revSListREC(NODE *root);
NODE * revSListOrder(NODE *root, int order);

NODE * mergeSList(NODE *root1, NODE *root2);
NODE * findDupInSList(NODE *root);
NODE * findLoopInSlist(NODE *root);
NODE * findNthElementFronTail(NODE *root, int n);

NODE * deleteSlist(NODE *root);




