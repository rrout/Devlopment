#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

bst_t * insertBstNode(bst_t *root, int data)
{
	if (root == NULL)
	{
		root = malloc(sizeof(bst_t));
		root->data = data;
		root->left = root->right = NULL;
		return root;
	}
	if (data > root->data)
		root->right = insertBstNode(root->right, data);
	else
		root->left = insertBstNode(root->left, data);
	return root;
}

bst_t * removeBstNode(bst_t *root, int data)
{

}

bst_t * searchBst(bst_t *root, int data)
{
	bst_t *p = root;
	while(p)
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

bst_t * getMinBstElem(bst_t *root)
{
	while(root && root->left)
		root =  root->left;
	return root;
}


bst_t * getMaxBstElem(bst_t *root)
{
	while(root && root->right)
		root =  root->right;
	return root;
}

int getBstHeight(bst_t *root)
{
	int lh = 0;
	int rh = 0;
	bst_t *p = root->left;
	while(p)
	{
		lh++;
		if(p->left)
			p = p->left;
		else
			p = p->right;
	}
	p = root->right;
	while(p)
	{
		rh++;
		if (p->right)
			p = p->right; 
		else
			p = p->left;
	}
	if(lh > rh)
		return (lh+1);
	else
		return (rh+1);
}

int getBstLeafCount(bst_t *root)
{
	int count = 0;
	if (root == NULL)
		return 0;
	if (root->left == NULL && root->right == NULL)
		return 1;

	count += getBstLeafCount(root->left);
	count += getBstLeafCount(root->right);
	return count;
}

int getBstNodeCount(bst_t *root)
{
	int count = 0;
	if (root == NULL)
		return 0;
	count += getBstNodeCount(root->left);
	count += getBstNodeCount(root->right);
	return count+1;
}

/* Print rioutienes */
void printBstPreOrder(bst_t *root)
{
	if(root == NULL)
		return;
	printf("%d\t",root->data);
	printBstPreOrder(root->left);
	printBstPreOrder(root->right);
}

void printBstInOrder(bst_t *root)
{
	if(root == NULL)
		return;
	printBstInOrder(root->left);
	printf("%d\t",root->data);
	printBstInOrder(root->right);
}
void printBstPostOrder(bst_t *root)
{
	if(root == NULL)
		return;
	printBstPostOrder(root->left);
	printBstPostOrder(root->right);
	printf("%d\t",root->data);
}

void printBstGraph(bst_t *root, int space)
{
	int i = 0;
	if(root != NULL)
	{
		printBstGraph(root->right, space+2);
		for( i = 0 ; i < space ; i++ )
			printf("  ");
		printf("%d\n", root->data);
		printBstGraph(root->left, space+2);
	}
}

/* Some extra stuffs */
bst_t * mirrorBst(bst_t *root)
{
}
bst_t * mirrorCopyBst(bst_t *src, bst_t *dst)
{

}
bst_t * copyBst(bst_t *src, bst_t *dst)
{

}

bst_t * findLeastCommonAncentor(bst_t *root, bst_t *nodeA, bst_t *nodeB)
{
	bst_t *left, *right;
	if (root == NULL)
		return root;
	if (root == nodeA || root == nodeB)
		return root;
	left = findLeastCommonAncentor(root->left, nodeA, nodeB);
	right = findLeastCommonAncentor(root->right, nodeA, nodeB);

	if (left && right)
		return root;
	if (left)
		return left;
	if (right)
		return right;
}

