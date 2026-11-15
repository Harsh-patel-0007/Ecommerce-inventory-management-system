#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../include/performance.h"

// Compare products by ID
int compareProducts(const void *a, const void *b)
{

    Product *p1 = (Product *)a;
    Product *p2 = (Product *)b;

    return (p1->id > p2->id) - (p1->id < p2->id);
}

// Linear Search
int linearSearch(Product products[], int count, int id)
{

    for (int i = 0; i < count; i++)
    {
        if (products[i].id == id)
            return i;
    }

    return -1;
}

// Binary Search
int binarySearchTest(Product products[], int count, int id)
{

    int low = 0;
    int high = count - 1;

    while (low <= high)
    {

        int mid = low + (high - low) / 2;

        if (products[mid].id == id)
            return mid;

        if (products[mid].id < id)
            low = mid + 1;
        else
            high = mid - 1;
    }

    return -1;
}

// Performance comparison
void benchmarkSearchAlgorithms(
    Product products[],
    int count,
    HashEntry hashTable[],
    BSTNode *root)
{

    if (count == 0)
    {
        printf("\nNo products available for testing!\n");
        return;
    }

    Product sortedProducts[MAX_PRODUCTS];

    for (int i = 0; i < count; i++)
        sortedProducts[i] = products[i];

    qsort(sortedProducts, count, sizeof(Product), compareProducts);

    int searchId = products[0].id;
    int repetitions = 100000;

    volatile int result;

    clock_t start, end;

    printf("\n===== SEARCH PERFORMANCE ANALYSIS =====\n");
    printf("Number of Products: %d\n", count);
    printf("Search Repetitions: %d\n", repetitions);

    // Linear Search
    start = clock();

    for (int i = 0; i < repetitions; i++)
        result = linearSearch(products, count, searchId);

    end = clock();

    printf("\nLinear Search: %.3f ms",
           1000.0 * (end - start) / CLOCKS_PER_SEC);

    // Binary Search
    start = clock();

    for (int i = 0; i < repetitions; i++)
        result = binarySearchTest(sortedProducts, count, searchId);

    end = clock();

    printf("\nBinary Search: %.3f ms",
           1000.0 * (end - start) / CLOCKS_PER_SEC);

    // Hash Table Search
    start = clock();

    for (int i = 0; i < repetitions; i++)
        result = searchHashTable(searchId, hashTable);

    end = clock();

    printf("\nHash Table Search: %.3f ms",
           1000.0 * (end - start) / CLOCKS_PER_SEC);

    // BST Search
    start = clock();

    for (int i = 0; i < repetitions; i++)
    {
        Product *found = searchBST(root, searchId);
        result = (found != NULL);
    }

    end = clock();

    printf("\nBST Search: %.3f ms\n",
           1000.0 * (end - start) / CLOCKS_PER_SEC);
}