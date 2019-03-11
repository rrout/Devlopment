#include <stdio.h>
#include <stdlib.h>

#ifndef __BST_H__
#define __BST_H__
typedef struct _bst {
	int data;
	struct _bst *left;
	struct _bst *right;
}bst_t;

bst_t * insertBstNode(bst_t *root, int data);
bst_t * removeBstNode(bst_t *root, int data);

bst_t * searchBst(bst_t *root, int data);
bst_t * getMinBstElem(bst_t *root);
bst_t * getMaxBstElem(bst_t *root);

int getBstHeight(bst_t *root);
int getBstLeafCount(bst_t *root);
int getBstNodeCount(bst_t *root);

/* Print rioutienes */
void printBstPreOrder(bst_t *root);
void printBstInOrder(bst_t *root);
void printBstPostOrder(bst_t *root);
void printBstGraph(bst_t *root, int space);

/* Some extra stuffs */
bst_t * mirrorBst(bst_t *root);
bst_t * mirrorCopyBst(bst_t *src, bst_t *dst);
bst_t * copyBst(bst_t *src, bst_t *dst);

bst_t * findLeastCommonAncentor(bst_t *root, bst_t *nodeA, bst_t *nodeB);
#endif /*__BST_H__*/
