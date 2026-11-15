#include <stdio.h>
#include "../include/product.h"
#include "../include/order.h"

// Place a new order
void placeOrder(Order orders[], int *rear, int *front,
                Product products[], int productCount)
{

    if (*rear == 99)
    {
        printf("\nOrder queue is full!\n");
        return;
    }

    Order newOrder;
    int found = 0;
    int index = -1;

    printf("\nEnter Order ID: ");
    scanf("%d", &newOrder.orderId);

    printf("Enter Product ID: ");
    scanf("%d", &newOrder.productId);

    printf("Enter Order Quantity: ");
    scanf("%d", &newOrder.quantity);

    if (newOrder.quantity <= 0)
    {
        printf("\nInvalid order quantity!\n");
        return;
    }

    // Search for the product
    for (int i = 0; i < productCount; i++)
    {

        if (products[i].id == newOrder.productId)
        {
            found = 1;
            index = i;
            break;
        }
    }

    if (!found)
    {
        printf("\nProduct does not exist!\n");
        return;
    }

    // Check available stock
    if (newOrder.quantity > products[index].quantity)
    {
        printf("\nInsufficient stock available!\n");
        printf("Available Quantity: %d\n",
               products[index].quantity);
        return;
    }

    if (*front == -1)
        *front = 0;

    (*rear)++;

    orders[*rear] = newOrder;

    saveOrderToFile(newOrder);

    printf("\nOrder placed successfully!\n");
}

// Process the first order
void processOrder(Order orders[], int *front, int rear,
                  Product products[], int productCount)
{

    if (*front == -1 || *front > rear)
    {
        printf("\nNo pending orders!\n");
        return;
    }

    Order currentOrder = orders[*front];

    int found = 0;

    // Find the ordered product
    for (int i = 0; i < productCount; i++)
    {

        if (products[i].id == currentOrder.productId)
        {

            found = 1;

            if (products[i].quantity >= currentOrder.quantity)
            {

                products[i].quantity -= currentOrder.quantity;

                saveProductsToFile(products, productCount);

                printf("\nOrder processed successfully!\n");
                printf("Order ID: %d\n", currentOrder.orderId);
                printf("Product: %s\n", products[i].name);
                printf("Remaining Stock: %d\n",
                       products[i].quantity);
            }
            else
            {

                printf("\nOrder cannot be processed!\n");
                printf("Insufficient stock available.\n");
            }

            break;
        }
    }

    if (!found)
    {
        printf("\nProduct not found. Order cannot be processed.\n");
    }

    (*front)++;
}

// Save order permanently in a file
void saveOrderToFile(Order order)
{

    FILE *fp = fopen("data/orders.txt", "a");

    if (fp == NULL)
    {
        printf("\nError opening order file!\n");
        return;
    }

    fprintf(fp, "%d %d %d\n",
            order.orderId,
            order.productId,
            order.quantity);

    fclose(fp);

    printf("Order saved successfully!\n");
}

// Display all saved orders
void displaySavedOrders()
{

    FILE *fp = fopen("data/orders.txt", "r");

    if (fp == NULL)
    {
        printf("\nNo saved orders found!\n");
        return;
    }

    Order order;

    printf("\n========== SAVED ORDERS ==========\n");

    while (fscanf(fp, "%d %d %d",
                  &order.orderId,
                  &order.productId,
                  &order.quantity) == 3)
    {

        printf("\nOrder ID: %d", order.orderId);
        printf("\nProduct ID: %d", order.productId);
        printf("\nQuantity: %d\n", order.quantity);
    }

    fclose(fp);
}