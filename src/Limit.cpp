
#include <iostream>
#include "OrderBook.h"


namespace LOB
{

    /**
     * @brief Standard constructor, setting all values to zero. Should only be used for dummy nodes.
    */
    Limit::Limit() : size(0), price(INT_MIN), numOrders(0),
                     headOrder(nullptr), tailOrder(nullptr){}

    /**
     * @brief Constructor that creates a new limit at a given price.
     * @param price is the price of the limit order.
     */
    Limit::Limit(int price) : size(0), price(price), numOrders(0)
    {
        //Creates dummy nodes at the head and tail
        headOrder = new Order();
        tailOrder = new Order();
        headOrder->next = tailOrder;
        tailOrder->prev = headOrder;
    }

    /**
     * @brief Standard destructor, deleting every node in the doubly linked order list.
     */
    Limit::~Limit()
    {
        while (headOrder != nullptr)
        {
            Order *nxt = headOrder->next;
            delete headOrder;
            headOrder = nxt;
        }
    }

    /**
     * @brief Returns true if the linked list contains no nodes (except for dummy nodes).
     */
    bool Limit::isEmpty()
    {
        return headOrder->next == tailOrder;
    }


    /**
     * @brief Adds a new node(order) at the end of the linked list
     * @param *newOrder - the new order to be inserted
    */
    void Limit::addOrder(Order *newOrder)
    {
        // Adds a new node at the end of the list, just before the dummy tail
        Order *currentLast = tailOrder->prev;
        currentLast->next = newOrder;
        newOrder->prev = currentLast;
        newOrder->next = tailOrder;
        tailOrder->prev = newOrder;

        // Increase volume and number of orders
        size += newOrder->size;
        numOrders++;
    }

    /**
     * @brief Returns the oldest order of the linked list.
     * @return the first active order that was inserted at the given price, or nullptr if it doesnt
     * exist.
     */
    Order *Limit::top()
    {
        if (headOrder->next != tailOrder)
        {
            return headOrder->next;
        }
        else
        {
            return nullptr;
        }
    }

  
    /**
     * @brief Removes an order from the list. Order needs to exist and cannot be a dummy node.
     * @param *order - Order to be removed
    */
    void Limit::removeOrder(Order *order)
    {
        order->prev->next = order->next;
        order->next->prev = order->prev;

         //Decrease number of orders
        numOrders--;


        //Decrease volume
        size -= order->size;

        //Free space
        delete order;
       
    }

    /**
     * @brief Updates the size of an existing order. Not used for deleting/insertion.
     * @param order which will be updated
     * @param newSize the new size of the order after updating
     */
    void Limit::updateOrder(Order *order, int newSize){
        size += (-order->size + newSize);
        order->size = newSize;


    }
}
