#ifndef ORDER_H
#define ORDER_H

#include "product.h"

typedef struct
{
    int orderId;
    int productId;
    int quantity;
} Order;

void placeOrder(Order orders[], int *rear, int *front,
                Product products[], int productCount);

void processOrder(Order orders[], int *front, int rear,
                  Product products[], int productCount);

void saveOrderToFile(Order order);
void displaySavedOrders();

#endif