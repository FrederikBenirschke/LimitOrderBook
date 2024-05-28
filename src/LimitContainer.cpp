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
    template <typename LimitT, typename OP>
    void LimitContainer<LimitT, OP>::removeLimit(LimitT *limit)
    {
        limits.erase(limit->price);
    }

    /**
     * @brief Removes a price from the container and updates the current maximum price.
     * @param limit will be removed from the container
     */
    template <typename LimitT, typename OP>
    void LimitContainer<LimitT, OP>::pop(LimitT *limit)
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
     * @brief Compares two prices according to the comparison provided by the operator OP.
     * @param a first int
     * @param b  second int
     * @return Returns -1 if a <b,
     *                  0 if a==b,
     *                  1 if a >b. Here < is provided by OP.
     */
    template <typename LimitT, typename OP>
    int LimitContainer<LimitT, OP>::cmp(const int a, const int b) const
    {

        if (OP()(a, b))
            return -1;

        if (OP()(b, a))
            return 1;

        return 0;
    }

    /**
     * @brief Searches the container for a price.
     * @param price that is searched for
     * @return Returns the limit container at the given price of found, or nullptr otherwise.
     */
    template <typename LimitT, typename OP>
    LimitT *LimitContainer<LimitT, OP>::search(int price)
    {
        if (limits.contains(price))
        {
            return limits[price];
        }
        else
        {
            return nullptr;
        }
    }


    /**
     * @brief Adds an order to the container. If the corresponding price container 
     * does not exist, it will also be created.
     * @param order to be inserted
     */
    template <typename LimitT, typename OP>
    void LimitContainer<LimitT, OP>::addOrder(Order *order)
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
    template <typename LimitT, typename OP>
    void LimitContainer<LimitT, OP>::deleteOrder(Order *order)
    {
        LimitT *limit = search(order->price);
        // updateOrder(order, 0);
        deleteOrderAtLimit(order, limit);
    }

     /**
     * @brief Deletes a given order at a given price point. If it is the last order, also
     * remove the limit container.
     * @param order to be deleted
     * @param limit price of the order
    */
    template <typename LimitT, typename OP>
    void LimitContainer<LimitT, OP>::deleteOrderAtLimit(Order *order, LimitT *limit)
    {

        // updateOrderAtLimit(order, limit, 0);
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
     * @warning  newSizeShould not be zero; use deleteOrderAtLimit instead.
     * The container limit needs to contain order.
     * 
    */
    template <typename LimitT, typename OP>
    void LimitContainer<LimitT, OP>::updateOrderAtLimit(Order *order, LimitT *limit, int newSize)
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
    template <typename LimitT, typename OP>
    void LimitContainer<LimitT, OP>::updateOrder(Order *order, int newSize)
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
    template <typename LimitT, typename OP>
    int LimitContainer<LimitT, OP>::topPrice()
    {
        if (!isEmpty())
        {
            return limits.rbegin()->first;
        }
        else
        {
            return -1;
        }
    }


     /**
     * @brief Returns first order at the top price.(First means that it has been in the limit container
     * the longest)
     * @return The order on top of the limit container of the maximum price.
    */
    template <typename LimitT, typename OP>
    Order *LimitContainer<LimitT, OP>::topOrder()
    {

        return limits.rbegin()->second->top();
    }


     /**
     * @brief Returns the limit container of the top price (sorted by the operator OP).
     * @return The limit container with  the maximal price.
    */
    template <typename LimitT, typename OP>
    LimitT *LimitContainer<LimitT, OP>::top()
    {
        return limits.rbegin()->second;
    }

    /* searchPricees if the current price is already contained in the limit tree. If not it adds a new node.
     */
     /**
     * @brief Adds a new order container, if the correspondong price is not in the limit container.
     * Has to search for the price first.
     * @param price to be searched for
     * @return The limit with the given price.
    */
    template <typename LimitT, typename OP>
    LimitT *LimitContainer<LimitT, OP>::addPrice(int price)
    {

        LimitT *limit = search(price);
        if (limit != nullptr)
        {
            return limit;
        }
        else
        {

            limits[price] = new LimitT(price);
        }
        return limits[price];
    }


     /**
     * @brief Checks if the limit container is empty, i.e. contains no orders.
     * @return True if there are no outstanding orders and false otherwise.
    */
    template <typename LimitT, typename OP>
    bool LimitContainer<LimitT, OP>::isEmpty()
    {
        return limits.empty();
    }

    template class LimitContainer<Limit, std::less<int>>;
    template class LimitContainer<Limit, std::greater<int>>;

}
