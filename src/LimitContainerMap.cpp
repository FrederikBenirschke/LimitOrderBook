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
    void LimitContainerMap<LimitT>::removeLimit(LimitT *limit)
    {
        limits.erase(limit->price);
    }

  
    /**
     * @brief Searches the container for a price.
     * @param price that is searched for
     * @return Returns the limit container at the given price of found, or nullptr otherwise.
     */
    template <typename LimitT>
    LimitT *LimitContainerMap<LimitT>::search(int price)
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
     * @brief Returns the limit container of the top price.
     * @return The limit container with  the maximal price.
    */
    template <typename LimitT>
    LimitT *LimitContainerMap<LimitT>::top()
    {
        return limits.rbegin()->second;
    }


      /**
     * @brief Returns the limit container of the bottom price.
     * @return The limit container with  the maximal price.
    */
    template <typename LimitT>
    LimitT *LimitContainerMap<LimitT>::bottom()
    {
        return limits.begin()->second;
    }

    /* searchPricees if the current price is already contained in the limit tree. If not it adds a new node.
     */
     /**
     * @brief Adds a new order container, if the correspondong price is not in the limit container.
     * Has to search for the price first.
     * @param price to be searched for
     * @return The limit with the given price.
    */
    template <typename LimitT>
    LimitT *LimitContainerMap<LimitT>::addPrice(int price)
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
    template <typename LimitT>
    bool LimitContainerMap<LimitT>::isEmpty()
    {
        return limits.empty();
    }



    template <typename LimitT>
    std::map<int,  LimitT*, std::greater<int>> LimitContainerMap<LimitT>::GetPriceMap()
    {
         std::map<int, LimitT*, std::greater<int>>  priceMap;
        for(auto& pair : limits){
            priceMap[pair.first] = pair.second;
        }
        return priceMap;

    }

    template class LimitContainerMap<Limit>;
   

}
