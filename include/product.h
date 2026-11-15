#ifndef PRODUCT_H
#define PRODUCT_H

#define MAX_PRODUCTS 1000

typedef struct
{
    int id;
    char name[50];
    char category[30];
    float price;
    int quantity;
    int minStock;
} Product;

void addProduct(Product products[], int *count);
void displayProducts(Product products[], int count);
void searchProduct(Product products[], int count);
void sortProductsByPrice(Product products[], int count);
void showLowStockProducts(Product products[], int count);
void saveProductsToFile(Product products[], int count);
void loadProductsFromFile(Product products[], int *count);
int binarySearch(Product products[], int count, int searchId);
void sortProductsById(Product products[], int count);
void updateProduct(Product products[], int count);

#endif