#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include "product.h"
#include "hash.h"
#include "bst.h"

void benchmarkSearchAlgorithms(
    Product products[],
    int count,
    HashEntry hashTable[],
    BSTNode *root);

#endif