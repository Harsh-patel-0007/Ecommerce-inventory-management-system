#include <stdio.h>
#include <stdlib.h>
#include "../include/bst.h"

// Create a new BST node
BSTNode *createNode(Product product)
{

    BSTNode *newNode = malloc(sizeof(BSTNode));

    if (newNode == NULL)
    {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    newNode->data = product;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Insert product into BST
BSTNode *insertBST(BSTNode *root, Product product)
{

    if (root == NULL)
    {
        return createNode(product);
    }

    if (product.id < root->data.id)
    {
        root->left = insertBST(root->left, product);
    }
    else if (product.id > root->data.id)
    {
        root->right = insertBST(root->right, product);
    }

    return root;
}

// Search product using BST
Product *searchBST(BSTNode *root, int productId)
{

    if (root == NULL)
        return NULL;

    if (productId == root->data.id)
        return &root->data;

    if (productId < root->data.id)
        return searchBST(root->left, productId);

    return searchBST(root->right, productId);
}

// Build BST using existing products
BSTNode *buildBST(Product products[], int count)
{

    BSTNode *root = NULL;

    for (int i = 0; i < count; i++)
    {
        root = insertBST(root, products[i]);
    }

    return root;
}

// Free allocated memory
void freeBST(BSTNode *root)
{

    if (root == NULL)
        return;

    freeBST(root->left);
    freeBST(root->right);

    free(root);
}