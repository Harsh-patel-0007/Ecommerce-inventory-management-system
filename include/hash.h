#ifndef HASH_H
#define HASH_H

#include "product.h"

#define HASH_SIZE 2003

typedef struct
{
    int productId;
    int productIndex;
    int occupied;
} HashEntry;

void buildHashTable(Product products[], int count,
                    HashEntry table[]);

int searchHashTable(int productId, HashEntry table[]);

#endif