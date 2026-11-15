#ifndef BST_H
#define BST_H

#include "product.h"

typedef struct BSTNode
{
    Product data;
    struct BSTNode *left;
    struct BSTNode *right;
} BSTNode;

BSTNode *insertBST(BSTNode *root, Product product);

Product *searchBST(BSTNode *root, int productId);

BSTNode *buildBST(Product products[], int count);

void freeBST(BSTNode *root);

#endif