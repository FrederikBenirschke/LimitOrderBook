#include <iostream>
#include <queue>

#include <assert.h>
#include "OrderBook.h"
namespace LOB
{
  
    /**
     * @brief Removes a price from the container and updates the current maximum price.
     * @param limit will be removed from the container
     */
    template <typename LimitT>
    void LimitContainer<LimitT>::pop(LimitT *limit)
    {

        Order *order = limit->top();
        if (order != nullptr)
        {
            // Decrease volume
            size -= order->size;
            // Remove from order container
            limit->removeOrder(order);
        }

        if (limit->isEmpty())
        {
            // If this was the last order in the list,
            //  remove the whole price limit.
            removeLimit(limit);
        }
    }

   
   

    /**
     * @brief Adds an order to the container. If the corresponding price container 
     * does not exist, it will also be created.
     * @param order to be inserted
     */
    template <typename LimitT>
    void LimitContainer<LimitT>::addOrder(Order *order)
    {

        LimitT *limit = addPrice(order->price);

        limit->addOrder(order);
        size += order->size;
    }


    /**
     * @brief Deletes a given order. Needs to find the corresponding limit first,
     * and is thus slower than deleteOrderAtLimit.
     * @param order to be deleted
    */
    template <typename LimitT>
    void LimitContainer<LimitT>::deleteOrder(Order *order)
    {
        LimitT *limit = search(order->price);
        deleteOrderAtLimit(order, limit);
    }

     /**
     * @brief Deletes a given order at a given price point. If it is the last order, also
     * remove the limit container.
     * @param order to be deleted
     * @param limit price of the order
    */
    template <typename LimitT>
    void LimitContainer<LimitT>::deleteOrderAtLimit(Order *order, LimitT *limit)
    {

        limit->removeOrder(order);
        if (limit->isEmpty())
        {
            removeLimit(limit);
        }
    }

     /**
     * @brief Updates the size of an order at a given price.
     * @param order to be updated
     * @param limit the price of the order
     * @param newSize the new size of the order
     * @warning  newSize should not be zero; use deleteOrderAtLimit instead.
     * The container limit needs to contain order.
     * 
    */
    template <typename LimitT>
    void LimitContainer<LimitT>::updateOrderAtLimit(Order *order, LimitT *limit, int newSize)
    {
        limit->updateOrder(order,newSize);
        size += (-order->size + newSize);
    }

     /**
     * @brief Updates an order to a new volume. Needs to find the price first.
     * @param order to be updated
     * @param newSize the new size of the order
     * @warning If limit is known use updateOrderAtLimit instead.
    */
    template <typename LimitT>
    void LimitContainer<LimitT>::updateOrder(Order *order, int newSize)
    {
        LimitT *limit = search(order->price);

        if (limit == nullptr)
        {

            return;
        }
        updateOrderAtLimit(order, limit, newSize);
    }

     /**
     * @brief The top price (sorted using the operator OP).
     * @return The maximum price in the container.
    */
    template <typename LimitT>
    int LimitContainer<LimitT>::topPrice()
    {
        if (!isEmpty())
        {
            return  top()->price;
        }
        else
        {
            return -1;
        }
    }


      /**
     * @brief The bottom price.
     * @return The minimum price in the container.
    */
    template <typename LimitT>
    int LimitContainer<LimitT>::bottomPrice()
    {
        if (!isEmpty())
        {
            return  bottom()->price;
        }
        else
        {
            return -1;
        }
    }



 

    template class LimitContainer<Limit>;

}
