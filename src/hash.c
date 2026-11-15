#include <stdio.h>
#include "../include/hash.h"

// Hash function
int hashFunction(int productId)
{
    return productId % HASH_SIZE;
}

// Insert product into hash table
void insertHashTable(int productId, int index,
                     HashEntry table[])
{

    int position = hashFunction(productId);

    // Linear probing for collision handling
    while (table[position].occupied)
    {

        if (table[position].productId == productId)
        {
            table[position].productIndex = index;
            return;
        }

        position = (position + 1) % HASH_SIZE;
    }

    table[position].productId = productId;
    table[position].productIndex = index;
    table[position].occupied = 1;
}

// Build hash table
void buildHashTable(Product products[], int count,
                    HashEntry table[])
{

    for (int i = 0; i < HASH_SIZE; i++)
    {
        table[i].occupied = 0;
    }

    for (int i = 0; i < count; i++)
    {
        insertHashTable(products[i].id, i, table);
    }
}

// Search product using hash table
int searchHashTable(int productId, HashEntry table[])
{

    int position = hashFunction(productId);
    int start = position;

    while (table[position].occupied)
    {

        if (table[position].productId == productId)
        {
            return table[position].productIndex;
        }

        position = (position + 1) % HASH_SIZE;

        if (position == start)
            break;
    }

    return -1;
}