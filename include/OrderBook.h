#pragma once
#include <string>
#include <unordered_map>
#include "Limit.h"
#include "LimitContainer.h"
namespace LOB
{


    /**
     * @brief The order book keeps track of all existing limit orders.
     * When a new order arrives it is autmatically matched with the current best bid/ask if possible and
     * otherwise added to the list of orders.
     * The order book is realized using separate data structures for the different price limits,
     * and another data structure for the list of orders at a given price point.
     * Prices are represented as integers, 100 represents 1.0.
     * 
     * @tparam LimitT - the data structure used for the orders at a given price.
     * The default is Limit, which is implemented using a doubly linked list.
     * @tparam LimitContainerT - data structure containing the prices of all buy orders.
     * Default is LimitContainer, which is implemented using std::map. Depending on the implementation
     * this should be represented by a red-black tree. By default the buys are in ascending order,
     * so that top() gives the largest bid.
     * @tparam LimitContainerU - Similar structure for the sell prices.
     * By default this uses the same LimitContainer as for the buys but in descending order.
     */
    template <typename LimitT = Limit,
    typename LimitContainerT=LimitContainer<LimitT,std::less<int>>,
    typename LimitContainerU=LimitContainer<LimitT,std::greater<int>>>
    class OrderBook
    {

    private:
   


    public:
        int                  currentId;
        LimitContainerT     *buyContainer;// Container with all buy orders
        LimitContainerU     *sellContainer; // Container with all sell orders

        int                                     askPrice;//current smallest sell order
        int                                     bidPrice;//current largest buy order
        std::unordered_map<int, LOB::Order*>    orderMap;//keeps track of the orderIds for each order



        
        OrderBook();//standard constructor, initializes empty limit containers
        int     spread();
        void    addOrder(Order *order, bool verbose=false);
        Order   *addOrder(int size, int price, OrderType orderType, bool verbose=false);
        void    cancelOrder(Order *order, bool verbose = false);
        // void    cancelOrder(int orderId, bool verbose = false);
        void    registerOrder(Order* order);
        void    unregisterOrder(Order* order);
        // void    explain();
        void    update();
        void    print();
    };
}
