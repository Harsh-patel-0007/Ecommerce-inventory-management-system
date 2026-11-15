#include <stdio.h>
#include "include/product.h"
#include "include/order.h"
#include "include/hash.h"
#include "include/bst.h"
#include "include/performance.h"

int main()
{

    Product products[MAX_PRODUCTS];
    int count = 0;
    
    Order orders[100];
    int front = -1;
    int rear = -1;

    HashEntry hashTable[HASH_SIZE];

    BSTNode *root = NULL;

    loadProductsFromFile(products, &count);

    buildHashTable(products, count, hashTable);

    root = buildBST(products, count);

    int choice;

    while (1)
    {

        printf("\n\n===== INVENTORY MANAGEMENT =====\n");
        printf("01. Add Product\n");
        printf("02. Display Products\n");
        printf("03. Search Product\n");
        printf("04. Sort Products by Price\n");
        printf("05. Show Low Stock Products\n");
        printf("06. Place order\n");
        printf("07. Process order\n");
        printf("08. Display Saved Orders\n");
        printf("09. Search Product using BST\n");
        printf("10. Update Product\n");
        printf("11. Sort Products by ID\n");
        printf("12. Search Product using Binary Search\n");
        printf("13. Performance Analysis\n");
        printf("14. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {

        case 1:
            if (count < 100)
            {
                addProduct(products, &count);

                buildHashTable(products, count, hashTable);

                freeBST(root);
                root = buildBST(products, count);
            }
            else
            {
                printf("Inventory is full!\n");
            }
            break;

        case 2:
            displayProducts(products, count);
            break;

        case 3:
        {
            int id;

            printf("\nEnter Product ID to search: ");
            scanf("%d", &id);

            int index = searchHashTable(id, hashTable);

            if (index != -1)
            {

                printf("\nProduct Found!\n");
                printf("ID: %d\n", products[index].id);
                printf("Name: %s\n", products[index].name);
                printf("Category: %s\n", products[index].category);
                printf("Price: %.2f\n", products[index].price);
                printf("Quantity: %d\n", products[index].quantity);
            }
            else
            {
                printf("\nProduct not found!\n");
            }

            break;
        }

        case 4:
            sortProductsByPrice(products, count);

            buildHashTable(products, count, hashTable);

            freeBST(root);
            root = buildBST(products, count);
            break;

        case 5:
            showLowStockProducts(products, count);
            break;

        case 6:
            placeOrder(orders, &rear, &front, products, count);
            break;

        case 7:
            processOrder(orders, &front, rear, products, count);

            freeBST(root);
            root = buildBST(products, count);

            break;

        case 8:
            displaySavedOrders();
            break;

        case 14:
            freeBST(root);
            printf("Exiting program...\n");
            return 0;

        case 9:
        {

            int id;

            printf("\nEnter Product ID to search: ");
            scanf("%d", &id);

            Product *result = searchBST(root, id);

            if (result != NULL)
            {

                printf("\nProduct Found using BST!\n");

                printf("Product ID: %d\n", result->id);
                printf("Name: %s\n", result->name);
                printf("Category: %s\n", result->category);
                printf("Price: %.2f\n", result->price);
                printf("Quantity: %d\n", result->quantity);
            }
            else
            {
                printf("\nProduct not found!\n");
            }

            break;
        }

        case 11:
            sortProductsById(products, count);

            buildHashTable(products, count, hashTable);

            freeBST(root);
            root = buildBST(products, count);

            saveProductsToFile(products, count);
            break;

        case 12:
        {
            int id;

            printf("\nEnter Product ID: ");
            scanf("%d", &id);

            // Sort products before binary search
            sortProductsById(products, count);

            int index = binarySearch(products, count, id);

            if (index != -1)
            {
                printf("\nProduct Found!\n");
                printf("ID: %d\n", products[index].id);
                printf("Name: %s\n", products[index].name);
                printf("Price: %.2f\n", products[index].price);
                printf("Quantity: %d\n", products[index].quantity);
            }
            else
            {
                printf("\nProduct not found!\n");
            }

            break;
        }

        case 13:
            benchmarkSearchAlgorithms(
                products,
                count,
                hashTable,
                root);
            break;

        case 10:
            updateProduct(products, count);

            // Rebuild BST to synchronize updated product details
            freeBST(root);
            root = buildBST(products, count);

            break;

        default:
            printf("Invalid choice!\n");
        }

        
    }

    return 0;
}