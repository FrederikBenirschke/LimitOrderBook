
#include <iostream>
#include <string>
#include "Book.h"
/**"
The limit class represents a price limit in the otder book. Limits are represented as RB- binary trees.
     */
// class LimitNode
// {
//     public:

//     int price;
//     int size;
//     LimitNode* left;
//     LimitNode* right;
//     LimitNode* parent;
//     Order* headOrder;
//     Order* tailOrder;
//     std::string color;

LimitNode::LimitNode() : size(0), price(0), numOrders(0), headOrder(nullptr), tailOrder(nullptr), color("BLACK") {}

/**
 * Constructor that creates a new limit at a given price.
 *
 * @param price is the price of the limit order.
 */
LimitNode::LimitNode(int pric) : size(0), price(pric),numOrders(0), headOrder(new Order()), tailOrder(new Order), color("BLACK") {
    headOrder->next = tailOrder;
    tailOrder->prev = headOrder;
}

/**
 * Standard destructor, deleting every node in the doubly linked order list.
 */
LimitNode::~LimitNode()
{
    while (headOrder != nullptr)
    {
        Order *nxt = headOrder->next;
        delete headOrder;
        headOrder = nxt;
    }
}

/**
 * Returns true if the size of the order is zero.
 *
 */
bool LimitNode::isEmpty()
{
    return headOrder->next == tailOrder;
}

/**
 * Returns true if the order is a buy order.
 *
 */
bool LimitNode::isBuy()
{
    return price > 0;
}

void LimitNode::addOrder(Order *newOrder)
{
    Order *currentLast = tailOrder->prev;
    currentLast->next = newOrder;
    newOrder->prev = currentLast;
    newOrder->next = tailOrder;
    tailOrder->prev = newOrder;
    
    size += newOrder->size;
    numOrders++;
}

// void LimitNode::updateOrder(Order *order, int newSize)
// {
//     order->size += newSize;
//     size += newSize;
// }

Order *LimitNode::top()
{
    return headOrder->next;
}

//  Order* pop(){
//     deleteOrder(headOrder->next);
// }

void LimitNode::deleteOrderAtTail()
{
    Order *last = tailOrder->prev;
    Order *newLast = last->prev;
    newLast->next = tailOrder;
    tailOrder->prev = newLast;
    
    delete last;
    numOrders--;
}

void LimitNode::deleteOrder(Order *order)
{
    order->prev->next = order->next;
    order->next->prev = order->prev;
    delete order;
    numOrders--;
}
