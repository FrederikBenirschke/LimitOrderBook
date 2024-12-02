#pragma once
#include <iostream>
#include <queue>
#include <assert.h>
#include <Limit.h>
#include <map>

namespace LOB
{

    

    /**
     * @brief Abstract container for a list of prices, and for each price a data structure containing all 
     * orders at that price point.
     * @tparam LimitT - Data structure containing all orders, by default a doubly linked list.
     */
    template <typename LimitT = Limit>
    class LimitContainer
    {

    private:

        int                             size;

        virtual void removeLimit(LimitT *limit) = 0;
        
    public:
        
       
        LimitContainer() : size(0) {}//standard constructor
        virtual ~LimitContainer() = default;

        virtual LimitT      *addPrice(int price) = 0;
        virtual LimitT      *search(int price) = 0;

        void        addOrder(Order *order);
        void        deleteOrder(Order *order);
        void        addOrderAtLimit(Order *order, LimitT *limit);
        void        deleteOrderAtLimit(Order *order, LimitT *limit);
        void        updateOrder(Order *order, int newSize);
        void        updateOrderAtLimit(Order *order, LimitT *limit, int newSize);

        virtual LimitT      *top() = 0;
        int                 topPrice();
        virtual LimitT      *bottom() = 0;
        int                 bottomPrice();
        void                pop(LimitT *limit);
        virtual bool        isEmpty() = 0;



        // Ordered_map containing all prices, only used for printing the current state of the LOB
        virtual std::map<int, LimitT*, std::greater<int>> GetPriceMap() = 0;


        

    };
}
