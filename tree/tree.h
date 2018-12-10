#include <stdio.h>

typedef struct _tnode {
	int data;
	struct _tnode *left;
	struct _tnode *right;
}TNODE;

TNODE * createTree(TNODE *root, int *arr, int numElem);
TNODE * insretElemToTree(TNODE * root, int data);
TNODE * deleteElemFromTree(TNODE *root, int data);

TNODE * searchElemInTree(TNODE *root, int data);

TNODE * copyTree(TNODE *root);
TNODE * mirrorTree(TNODE * root);


int isCopyTree(TNODE *root1, TNODE *root2);
int isMirrorTree(TNODE *root1, TNODE *root2);

int hightTree(TNODE *root);
TNODE * getMaxElem(TNODE *root);
TNODE * getMinElem(TNODE *root);

void printTreePreorder(TNODE *root);
void printTreeInorder(TNODE *root);
void printTreePostorder(TNODE *root);
void printTreeGRAPH(TNODE *roo, int space);

	