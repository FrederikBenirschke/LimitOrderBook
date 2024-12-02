#pragma once
#include <iostream>
#include <queue>
#include <assert.h>
#include <Limit.h>
#include <map>

namespace LOB
{

    

    /**
     * @brief Container for a list of prices, and for each price a data structure containing all 
     * orders at that price point. Implementation based on a bucket queue which provides insertion/deletion
     *  in amortized constant time.
     * Resizes dynamically.
     * 
     * TODO: Downsizing once buckets are emptied and allowing the min price to shift (currently always 1).
     *
     * @tparam LimitT - Data structure containing all orders, by default a doubly linked list.
     */
    template <typename LimitT = Limit>
    class LimitContainerBucket: public LimitContainer<LimitT>
    {


    private:

       
        int capacity;
        const int minPrice = 1;
        LimitT** buckets;
        int usedBuckets;



        void removeLimit(LimitT *limit) override;


         /**
         * @brief Dynamically resizies the bucket queue to a new capacity.
         * @param newCapacity is the new capacity
         */
        void resize(int newCapacity) {
        LimitT ** newBuckets = new LimitT*[newCapacity];
        
        for (int i = 0; i < newCapacity; ++i) {
            newBuckets[i] = nullptr;
        }
        for (int i = 0; i < capacity; ++i) {
            newBuckets[i] = buckets[i];
        }
        
        delete[] buckets;   
        buckets = newBuckets;
        capacity = newCapacity;
        }


         /**
         * @brief Converts a price to the corresponding bucket index.
         * @param price price to be converted 
         * @return Returns the index of buckets such that buckets[index] = price.
         */
        int priceToIndex(int price) const {
            if (price < minPrice) {
                throw std::out_of_range("Price is below the minimum supported value.");
            }
            return price - minPrice;
        }


        
    public:

        
        
       LimitContainerBucket(int initialCapacity= 100):  capacity(initialCapacity), usedBuckets(0)
        {
            buckets = new LimitT*[capacity];
             for (int i = 0; i < capacity; ++i) {
            buckets[i] = nullptr;
        }
        
        }

        ~LimitContainerBucket() {delete[] buckets;}


        LimitT      *addPrice(int price) override;
        LimitT      *search(int price) override;

        LimitT      *top() override;
        LimitT      *bottom() override;
        bool        isEmpty() override;

        std::map<int, LimitT*, std::greater<int>> GetPriceMap() override;
        


     
    };
}
