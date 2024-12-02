#pragma once
#include <string>
#include <unordered_map>
#include "Limit.h"
#include "LimitContainer.h"
#include "LimitContainerMap.h"
#include "LimitContainerBucket.h"
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
     * @tparam LimitContainerT - data structure containing the prices of all buy/sell orders.
     * Uses the same data structure for both buy and sell orders, the difference is that buy orders access 
     * the top price by default, sell orders the bottom price.
     * Default is LimitContainer, which is implemented using std::map(which is a Red-Black tree in clang/g++)
     */
    template <typename LimitT = Limit,
    typename LimitContainerT=LimitContainerMap<LimitT>>
    class OrderBook
    {

    private:
   


    public:
        int                  currentId;
        LimitContainerT     *buyContainer;// Container with all buy orders
        LimitContainerT     *sellContainer; // Container with all sell orders

        int                                     askPrice;//current smallest sell order
        int                                     bidPrice;//current largest buy order
        std::unordered_map<int, LOB::Order*>    orderMap;//keeps track of the orderIds for each order



        
        OrderBook(); //standard constructor, initializes empty limit containers
        ~OrderBook() {delete buyContainer; delete sellContainer;}
        int     spread();
        void    addOrder(Order *order, bool verbose=false);
        Order   *addOrder(int size, int price, OrderType orderType, bool verbose=false);
        void    cancelOrder(Order *order, bool verbose = false);
        void    registerOrder(Order* order);
        void    unregisterOrder(Order* order);
        void    update();
        void    print();
    };



   
}
