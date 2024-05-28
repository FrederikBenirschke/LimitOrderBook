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
     * @tparam OP - comparison operator used to order the prices. By default in ascending order.
     */
    template <typename LimitT = Limit, typename OP = std::less<int>>
    class LimitContainer
    {

    private:
        int         cmp(const int a, const int b) const;
        LimitT      *maximum(LimitT *node);
        LimitT      *minimum(LimitT *node);
        LimitT      *addLimitHelper(LimitT *parent, int price, int dir);
      
        
    public:
        int                             size;
        std::map<int, LimitT *, OP>     limits;//map containing all prices and all corresponding orders
       
        LimitContainer() : size(0) {}//standard constructor
        ~LimitContainer();

        LimitT      *addPrice(int price);
        LimitT      *search(int price);
        void        addOrder(Order *order);
        void        deleteOrder(Order *order);
        void        addOrderAtLimit(Order *order, LimitT *limit);
        void        deleteOrderAtLimit(Order *order, LimitT *limit);
        void        updateOrder(Order *order, int newSize);
        void        updateOrderAtLimit(Order *order, LimitT *limit, int newSize);
        void        removeLimit(LimitT *limit);
        LimitT      *top();
        int         topPrice();
        Order       *topOrder();
        void        pop(LimitT *limit);
        bool        isEmpty();
    };
}
