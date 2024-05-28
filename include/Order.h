#pragma once
namespace LOB{
    /// @brief Every limit order is either a buy or sell order.
    enum OrderType {Buy, Sell} ;

    /// @brief Represents an order in the limit book. Every order has a price and volume
    // and an order type, which can be either a sell or buy order. Orders are nodes in a doubly linked list.
    // Allows insertion and deletion at any point in O(1).
    class Order
    {
    public:
        int         orderId;
        int         size;
        int         price;
        OrderType   orderType;

        //Used for implementing the double linked list:
        Order       *next;
        Order       *prev;

    
        
        /**
         * @brief Standard constructor that creates a new empty order.
         * By default price = 0, size =0 and OrderType = Buy. Should only be used to
         * initialize empty orders, for example dummy nodes at the head and tail of the linked list.
         */
        Order(): size(0), price(0), next(nullptr), prev(nullptr),orderId(0){}

        

        /**
         * @brief Constructor that creates a new order.
         * @param size is the number of of buys/sells in the order
         * @param price the price for the limit order. Note that this is not necessary the sell/buy price
         * since limit orders are matched automatically with the current largest bid/smallest ask.
         * @param orderType determines if the order is a buy or sell order.
         */
        Order(int size, int price, OrderType orderType) :
        price(price),size(size), orderType(orderType),next(nullptr), prev(nullptr),orderId(0) {}

    };
}

