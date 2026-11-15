#include <stdio.h>
#include "../include/product.h"

void addProduct(Product products[], int *count)
{

    printf("\nEnter Product ID: ");
    scanf("%d", &products[*count].id);

    printf("Enter Product Name: ");
    scanf(" %49[^\n]", products[*count].name);

    printf("Enter Category: ");
    scanf(" %29[^\n]", products[*count].category);

    printf("Enter Price: ");
    scanf("%f", &products[*count].price);

    printf("Enter Quantity: ");
    scanf("%d", &products[*count].quantity);

    printf("Enter Minimum Stock: ");
    scanf("%d", &products[*count].minStock);

    (*count)++;

    printf("\nProduct added successfully!\n");

    saveProductsToFile(products, *count);
}

void displayProducts(Product products[], int count)
{

    if (count == 0)
    {
        printf("\nNo products available!\n");
        return;
    }

    printf("\n========== PRODUCT INVENTORY ==========\n");

    for (int i = 0; i < count; i++)
    {

        printf("\nProduct ID: %d", products[i].id);
        printf("\nName: %s", products[i].name);
        printf("\nCategory: %s", products[i].category);
        printf("\nPrice: %.2f", products[i].price);
        printf("\nQuantity: %d", products[i].quantity);
        printf("\nMinimum Stock: %d\n", products[i].minStock);
    }
}

void searchProduct(Product products[], int count)
{

    int searchId;
    int found = 0;

    printf("\nEnter Product ID to search: ");
    scanf("%d", &searchId);

    for (int i = 0; i < count; i++)
    {

        if (products[i].id == searchId)
        {

            printf("\nProduct Found!\n");
            printf("ID: %d\n", products[i].id);
            printf("Name: %s\n", products[i].name);
            printf("Category: %s\n", products[i].category);
            printf("Price: %.2f\n", products[i].price);
            printf("Quantity: %d\n", products[i].quantity);
            printf("Minimum Stock: %d\n", products[i].minStock);

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("\nProduct not found!\n");
    }
}

// Merge two sorted portions of the array
void merge(Product products[], int left, int mid, int right)
{

    int n1 = mid - left + 1;
    int n2 = right - mid;

    Product L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = products[left + i];

    for (int j = 0; j < n2; j++)
        R[j] = products[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2)
    {

        if (L[i].price <= R[j].price)
            products[k++] = L[i++];
        else
            products[k++] = R[j++];
    }

    while (i < n1)
        products[k++] = L[i++];

    while (j < n2)
        products[k++] = R[j++];
}

// Merge Sort algorithm
void mergeSort(Product products[], int left, int right)
{

    if (left < right)
    {

        int mid = left + (right - left) / 2;

        mergeSort(products, left, mid);
        mergeSort(products, mid + 1, right);

        merge(products, left, mid, right);
    }
}

// Sort products by price
void sortProductsByPrice(Product products[], int count)
{

    if (count == 0)
    {
        printf("\nNo products available to sort!\n");
        return;
    }

    mergeSort(products, 0, count - 1);

    printf("\nProducts sorted by price successfully!\n");
}

// Swap two products
void swap(Product *a, Product *b)
{
    Product temp = *a;
    *a = *b;
    *b = temp;
}

// Maintain Min Heap property
void minHeapify(Product heap[], int n, int i)
{

    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && heap[left].quantity < heap[smallest].quantity)
        smallest = left;

    if (right < n && heap[right].quantity < heap[smallest].quantity)
        smallest = right;

    if (smallest != i)
    {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, n, smallest);
    }
}

// Display products with low stock using Min Heap
void showLowStockProducts(Product products[], int count)
{

    Product heap[MAX_PRODUCTS];
    int heapSize = 0;

    for (int i = 0; i < count; i++)
    {

        if (products[i].quantity <= products[i].minStock)
        {
            heap[heapSize++] = products[i];
        }
    }

    if (heapSize == 0)
    {
        printf("\nNo low-stock products found!\n");
        return;
    }

    // Build Min Heap
    for (int i = heapSize / 2 - 1; i >= 0; i--)
    {
        minHeapify(heap, heapSize, i);
    }

    printf("\n========== LOW STOCK ALERT ==========\n");

    while (heapSize > 0)
    {

        printf("\nProduct: %s", heap[0].name);
        printf("\nProduct ID: %d", heap[0].id);
        printf("\nAvailable Quantity: %d", heap[0].quantity);
        printf("\nMinimum Required Stock: %d\n", heap[0].minStock);

        heap[0] = heap[heapSize - 1];
        heapSize--;

        if (heapSize > 0)
            minHeapify(heap, heapSize, 0);
    }
}

void saveProductsToFile(Product products[], int count)
{

    FILE *fp = fopen("data/products.txt", "w");

    if (fp == NULL)
    {
        printf("\nError saving products!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {

        fprintf(fp, "%d|%s|%s|%.2f|%d|%d\n",
                products[i].id,
                products[i].name,
                products[i].category,
                products[i].price,
                products[i].quantity,
                products[i].minStock);
    }

    fclose(fp);

    printf("\nProducts saved successfully!\n");
}

void loadProductsFromFile(Product products[], int *count)
{

    FILE *fp = fopen("data/products.txt", "r");

    if (fp == NULL)
    {
        *count = 0;
        return;
    }

    *count = 0;

    while (*count < MAX_PRODUCTS &&
           fscanf(fp, "%d|%49[^|]|%29[^|]|%f|%d|%d",
                  &products[*count].id,
                  products[*count].name,
                  products[*count].category,
                  &products[*count].price,
                  &products[*count].quantity,
                  &products[*count].minStock) == 6)
    {

        (*count)++;
    }

    fclose(fp);

    printf("\n%d products loaded successfully!\n", *count);
}

// Binary Search using Product ID
int binarySearch(Product products[], int count, int searchId)
{

    int low = 0;
    int high = count - 1;

    while (low <= high)
    {

        int mid = low + (high - low) / 2;

        if (products[mid].id == searchId)
        {
            return mid;
        }

        else if (products[mid].id < searchId)
        {
            low = mid + 1;
        }

        else
        {
            high = mid - 1;
        }
    }

    return -1;
}

void sortProductsById(Product products[], int count)
{

    // Sort products by Product ID using Bubble Sort
    for (int i = 0; i < count - 1; i++)
    {

        for (int j = 0; j < count - i - 1; j++)
        {

            if (products[j].id > products[j + 1].id)
            {

                Product temp = products[j];
                products[j] = products[j + 1];
                products[j + 1] = temp;
            }
        }
    }

    printf("\nProducts sorted by ID successfully!\n");
}


//update the products in the inventory 
void updateProduct(Product products[], int count)
{
    int id, choice;
    int found = -1;

    printf("\nEnter Product ID to update: ");
    scanf("%d", &id);

    // Search for the product
    for (int i = 0; i < count; i++)
    {
        if (products[i].id == id)
        {
            found = i;
            break;
        }
    }

    if (found == -1)
    {
        printf("\nProduct not found!\n");
        return;
    }

    printf("\nProduct Found!");
    printf("\nProduct Name: %s", products[found].name);

    printf("\n\nWhat do you want to update?");
    printf("\n1. Product Name");
    printf("\n2. Category");
    printf("\n3. Price");
    printf("\n4. Quantity");
    printf("\n5. Minimum Stock");
    printf("\nEnter your choice: ");

    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        printf("Enter new product name: ");
        scanf(" %49[^\n]", products[found].name);
        break;

    case 2:
        printf("Enter new category: ");
        scanf(" %29[^\n]", products[found].category);
        break;

    case 3:
        printf("Enter new price: ");
        scanf("%f", &products[found].price);
        break;

    case 4:
        printf("Enter new quantity: ");
        scanf("%d", &products[found].quantity);
        break;

    case 5:
        printf("Enter new minimum stock: ");
        scanf("%d", &products[found].minStock);
        break;

    default:
        printf("\nInvalid choice!\n");
        return;
    }

    // Save updated product details
    saveProductsToFile(products, count);

    printf("\nProduct updated successfully!\n");
}