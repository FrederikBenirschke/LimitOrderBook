#pragma once
#include "Order.h"
namespace LOB{
  

    /**
     * @brief Implementation of doubly linked list that contains all orders at a given price.
     * Allows for insertion/deletion in O(1) time.
     */
    class Limit
    {


    private:
        //Dummy nodes at the head and tail to simplify insertion/deletion
        Order*      headOrder;
        Order*      tailOrder;

    public:
        
        int         price;
        int         size;
        int         numOrders;

        Limit();
        Limit(int price);
        ~Limit();


        Order*      top();
        void        pop();
        void        addOrder(Order *order);
        void        removeOrder(Order *order);
        void        updateOrder(Order *order, int newSize);
        bool        isEmpty();


        

    };
}