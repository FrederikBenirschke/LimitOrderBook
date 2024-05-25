
# include "Book.h"

/**
The order class represents an order in the limit order book. The orders are implemented as doubly linked lists.
This guarantess
     */
// class Order
// {
// public:
// int orderId;
// Order *next;
// Order *prev;
// int size;
// int price;

/**
 * Standard constructor that creates a new order, sets prize and size to zero by default.
 *
 *
 */
Order::Order() : size(0), price(0), next(nullptr), prev(nullptr) {}

/**
 * Constructor that creates a new order and set the price, size.
 *
 * @param siz is the nummber of shares that should be sold/bought. A positive size indicates a buy order,
 *  a negative price a sell order.
 *  @param pric is the price of the current order.
 */
Order::Order(int siz, int pric) : size(siz), price(pric), next(nullptr), prev(nullptr) {}

/**
 * Returns true if the size of the order is zero.
 *
 */
bool Order::isEmpty()
{
    return price == 0;
}

/**
 * Returns true if the order is a buy order.
 *
 */
bool Order::isBuy()
{
    return price > 0;
}

