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
    void LimitContainerBucket<LimitT>::removeLimit(LimitT *limit)
    {
        int index = priceToIndex(limit->price);
        if (index >= capacity || buckets[index]==nullptr) {
           return;
        }

       
        delete buckets[index];
        buckets[index] = nullptr;
        usedBuckets--;
    }

  
    /**
     * @brief Searches the container for a price.
     * @param price that is searched for
     * @return Returns the limit container at the given price of found, or nullptr otherwise.
     */
    template <typename LimitT>
    LimitT *LimitContainerBucket<LimitT>::search(int price)
    {
        for(int i =0; i < capacity; i++){
            if(buckets[i]!=nullptr && buckets[i]->price == price){
                return buckets[i];
            }
        }
        return nullptr;
    }


  

 
     
     /**
     * @brief Returns the limit container of the top price.
     * @return The limit container with  the maximal price.
    */
    template <typename LimitT>
    LimitT *LimitContainerBucket<LimitT>::top()
    {
        if (usedBuckets == 0){
            return nullptr;
        }
         for(int i = capacity - 1; i >=0; i--){
            if(buckets[i]!=nullptr){
                return buckets[i];
            }
        }
        return nullptr;
    }


      /**
     * @brief Returns the limit container of the bottom price.
     * @return The limit container with  the maximal price.
    */
    template <typename LimitT>
    LimitT *LimitContainerBucket<LimitT>::bottom()
    {
         if (usedBuckets == 0){
            return nullptr;
        }
        for(int i = 0; i < capacity; i++){
            if(buckets[i]!=nullptr){
                return buckets[i];
            }
        }
        return nullptr;
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
    LimitT *LimitContainerBucket<LimitT>::addPrice(int price)
    {

        int index = priceToIndex(price);
        if (index>= capacity){
            resize(index+1);
        }
        if (buckets[index] != nullptr) {
            return buckets[index]; 
        }

        buckets[index] = new LimitT(price);  
        usedBuckets++; 
        return buckets[index];
    }


     /**
     * @brief Checks if the limit container is empty, i.e. contains no orders.
     * @return True if there are no outstanding orders and false otherwise.
    */
    template <typename LimitT>
    bool LimitContainerBucket<LimitT>::isEmpty()
    {
        return usedBuckets == 0;
    }



    template <typename LimitT>
    std::map<int,  LimitT*, std::greater<int>> LimitContainerBucket<LimitT>::GetPriceMap()
    {
        std::map<int, LimitT*, std::greater<int>>  priceBucket;
        for(int i =0; i < capacity; i++){
            LimitT *limit = buckets[i];
            if (limit !=nullptr){
                 priceBucket[limit->price] = limit;
            }
           
        }
        return priceBucket;

    }

    template class LimitContainerBucket<Limit>;

}
