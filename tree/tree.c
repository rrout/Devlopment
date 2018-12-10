#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

int main()
{
	int arr[10] = { 100, 1, 5, 55, 1001, 2001, 301, 555, 777, 503};
	TNODE *root = NULL;
	TNODE *search = NULL;
	root = createTree(root, arr, sizeof(arr)/sizeof(arr[0]));
	printTreeGRAPH(root, 1);
	root = root = insretElemToTree(root,5000);
	printTreeGRAPH(root, 1);
	return 1;
}

TNODE * createTree(TNODE *root, int *arr, int numElem)
{
	int i;
	for (i = 0; i < numElem; i++)
	{
		root = insretElemToTree(root, arr[i]);
	}
	return root;
}
TNODE * insretElemToTree(TNODE * root, int data)
{
	if(!root)
	{
		root = (TNODE *) malloc (sizeof(TNODE));
		root->data = data;
		root->left = root->right = NULL;
		return root;
	}
	if (data < root->data)
		root->left = insretElemToTree(root->left, data);
	else
		root->right = insretElemToTree(root->right, data);
		
	return root;
}
TNODE * deleteElemFromTree(TNODE *root, int data)
{

}

TNODE * searchElemInTree(TNODE *root, int data)
{
	TNODE *p = root;
	if(!root)
		return NULL;
	while(p != NULL)
	{
		if (data == p->data)
			return p;
		else if (data < p->data)
			p = p->left;
		else
			p = p->right;			
	}
	return NULL;
}

TNODE * searchElemInTreeREC(TNODE *root, int data)
{
	TNODE *p;
	if(!root)
		return NULL;
	if (root->data == data)
		return root;
	else if (data < p->data)
		p  = searchElemInTreeREC(root->left, data);
	else
		p = searchElemInTreeREC(root->right, data);
		
	return p;	
}

TNODE * buildCopyTree(TNODE *root)
{
	TNODE *p;
	if (!root)
		return root;
	p = (TNODE *) malloc (sizeof(TNODE));
	p->data = root->data;
	p->left = buildCopyTree(root->left);
	p->right = buildCopyTree(root->right);
	
	return p;
}

TNODE * buildMirrorTree(TNODE * root)
{
	TNODE *p;
	if (!root)
		return root;
	p = (TNODE *) malloc (sizeof(TNODE));
	p->data = root->data;
	p->left = buildMirrorTree(root->right);
	p->right = buildMirrorTree(root->left);
	
	return p;
}

TNODE * mirrorTheTree(TNODE * root)
{
	TNODE * p;
	if (!root)
		return NULL;
	mirrorTheTree(root->left);
	mirrorTheTree(root->right);
	p = root->right;
	root->right = root->left;
	root->left = p;
	
	return root;
}


int isCopyTree(TNODE *root1, TNODE *root2)
{
	if (root1 == NULL && root2 == NULL)
		return 1;
	else if (root1 != NULL && root2 != NULL && root1->data == root2->data)
		return 1;
	else
		return 0;
		
	return (root1->data == root2->data &&
		isCopyTree(root1->left, root2->left) &&
		isCopyTree(root1->right, root2->right));
}

int isMirrorTree(TNODE *root1, TNODE *root2)
{

}

int hightTree(TNODE *root)
{
	int lh = 0;
	int rh = 0;
	TNODE *p = root;
	while (p != NULL)
	{
		lh++;
		if(p->left)
			p = p->left;
		else
			p = p->right;
	}
	p = root;
	while (p != NULL)
	{
		rh++;
		if(p->right)
			p = p->right;
		else
			p = p->left;
	}
	if(lh > rh)
		return lh+1;
	else
		return rh+1;
}

int hightTreeREC(TNODE *root)
{
	int lh = 0;
	int rh = 0;
	if(!root)
		return 1;
	lh = hightTreeREC(root->left);
	rh = hightTreeREC(root->left);
	
	if(lh > rh)
		return lh+1;
	else
		return rh+1;
	
}

TNODE * getMaxElem(TNODE *root)
{
	while(root->right != NULL)
		root = root->right;
		
	return root;	
}

TNODE * getMinElem(TNODE *root)
{
	while(root->left != NULL)
		root = root->left;
		
	return root;
}

TNODE * getMaxElemREC(TNODE *root)
{
	TNODE *temp;
	if (root == NULL || root->right == NULL)
		return root;		
	temp = getMaxElemREC(root->right);
	return temp;
}

TNODE * getMinElemREC(TNODE *root)
{
	TNODE *temp;
	if (root == NULL || root->left == NULL)
		return root;
	temp = getMinElemREC(root->left);
	return temp;
}

void printTreePreorder(TNODE *root)
{
	if(root != NULL)
	{
		printf("%d\t", root->data);
		printTreePreorder(root->left);
		printTreePreorder(root->right);
	}
}
void printTreeInorder(TNODE *root)
{
	if(root != NULL)
	{
		printTreeInorder(root->left);
		printf("%d\t", root->data);
		printTreeInorder(root->right);
	}
}
void printTreePostorder(TNODE *root)
{
	if(root != NULL)
	{
		printTreePostorder(root->left);
		printTreePostorder(root->right);
		printf("%d\t", root->data);
	}
}
void printTreeGRAPH(TNODE *root, int space)
{
	int i;
	if(root != NULL)
	{
		printTreeGRAPH(root->left, space+1);
		for(i = 0; i < space; i++)
			printf("     ");
		printf("%d\n", root->data);
		printTreeGRAPH(root->right, space+1);
	}
}