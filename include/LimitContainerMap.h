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
     * orders at that price point. Implementation based on std::map for effective insertion/deletion.
     * @tparam LimitT - Data structure containing all orders, by default a doubly linked list.
     */
    template <typename LimitT = Limit>
    class LimitContainerMap: public LimitContainer<LimitT>
    {


    private:

       

        void removeLimit(LimitT *limit) override;
        
    public:

        std::map<int, LimitT *>     limits;//map containing all prices and all corresponding orders
        
       
        LimitContainerMap(){}//standard constructor
         ~LimitContainerMap() {};

        LimitT      *addPrice(int price) override;
        LimitT      *search(int price) override;

        LimitT      *top() override;
        LimitT      *bottom() override;
        bool        isEmpty() override;

        std::map<int, LimitT*, std::greater<int>> GetPriceMap() override;
        


     
    };
}
