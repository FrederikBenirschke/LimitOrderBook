#include <iostream>
#include <assert.h>
#include <set>
#include <vector>
#include <stack>
#include <sstream>
#include <iomanip>
#include <map>
#include <random>
#include <assert.h>

// Macro to fill a line with a prescribed nuber of -
#define hfill(n) (std::cout << std::string(n, '-') << "\n")
#define width 40


// #include "Order.h"
// #include "Limit.h"
// #include "LimitContainer.h"
#include "OrderBook.h"
namespace LOB
{

     /**
     * @brief Standard constructor. Initializes two limit containers, one for sell order and 
     * one for buy orders.
    */
    template <typename LimitT, typename LimitContainerT, typename LimitContainerU>
    OrderBook<LimitT, LimitContainerT, LimitContainerU>::OrderBook() :
     currentId(0), buyContainer(nullptr), sellContainer(nullptr), askPrice(INT_MAX), bidPrice(INT_MIN)
    {
        buyContainer = new LimitContainerT();
        sellContainer = new LimitContainerU();
    }


    /**
     * @brief Returns the current bid-ask spread of the order book.
     * @return The difference between current bid and ask price.
    */
    template <typename LimitT, typename LimitContainerT, typename LimitContainerU>
    int OrderBook<LimitT, LimitContainerT, LimitContainerU>::spread()
    {
        return askPrice - bidPrice;
    }

    /**
     * @brief Adds an order to the limit book. First tries to match the order
     * with the exisiting buy/sell order. If that is not possible the order is added to the order book.
     * @param order the new order to be added
     * @param verbose if true, explains the trades that are performed
    */
    template <typename LimitT, typename LimitContainerT, typename LimitContainerU>
    void OrderBook<LimitT, LimitContainerT, LimitContainerU>::addOrder(Order *order, bool verbose)
    {
        if (order == nullptr || order->size <= 0)
        {
            //Can only add non-empty order with positive size.
            return;
        }


        if (order->orderType == Buy)
        {
            //Is a buy order?
            if(verbose){
                std::cout<< "New buy order incoming: (Price: " << order->price;
                std::cout<< ", " << "Size: " << order->size <<")."<<std::endl;
                std::cout<<"\n";

            }
            while (!sellContainer->isEmpty() && order->size > 0 && sellContainer->topPrice() <= order->price)
            {
                // There is a matching sell order?
                LimitT *limit = sellContainer->top();

                Order *sellOrder = sellContainer->topOrder();
                int sellSize = sellOrder->size;

                if (order->size >= sellSize)
                {
                    // Order size exceeds the first visible sell order?
                    // Then delete the first sell order and reduce the buy order accordingly
                    // Proceed recursively
                    order->size -= sellSize;
                    if(verbose){
                    std::cout<< "Bought " << sellOrder->size << " units at price " <<sellOrder->price <<"."<<std::endl;
                    
                    }
                    unregisterOrder(sellOrder);
                    sellContainer->pop(limit);
                  
                }
                else
                {

                    if(verbose){
                    std::cout<< "Bought " << order->size << " units at price" <<sellOrder->price <<"."<<std::endl;
                    std::cout<<"\n";
                    }

                    // Sell order can fully absorb the buy order?
                    sellContainer->updateOrderAtLimit(sellOrder, limit, sellSize - order->size);
                    //The order can now be discarded
                    order->size = 0;
                    break;
                }
            }
            if (order != nullptr && order->size > 0)
            {
                //Ignore orders that have been processed
                buyContainer->addOrder(order);
                registerOrder(order);
                if(verbose){
                std::cout<< "Buy order only partially filled. Remaining volume: " <<order->size << std::endl;
                 std::cout<< "Remaining buy order added to the order book." << std::endl;
                
                }
            }
            else{
                if(verbose){
                std::cout<< "Buy order filled." << std::endl;
                
                }
            }
        }

        if (order->orderType == Sell)
        {
            // Is sell order?
            //Everything works the same way, except that buy and sell are interchanged
            if(verbose){
                std::cout<< "New sell order incoming: (Price: " << order->price;
                std::cout<< ", " << "Size: " << order->size <<")."<<std::endl;
                std::cout<<"\n";
            }
            while (!buyContainer->isEmpty() && (order->size > 0) && (order->price <= buyContainer->topPrice()))
            {
                // There is a matching buy order?

                LimitT *limit = buyContainer->top();
                Order *buyOrder = limit->top();
                int buySize = buyOrder->size;

                if (order->size >= buySize)
                {
                    if(verbose){
                    std::cout<< "Sold " << buySize << " units at price " <<buyOrder->price <<"."<<std::endl;
                    std::cout<<"\n";
                    }
                    // Order size exceeds the first visible buy order ?
                    // Then delete the first sell order and reduce the buy order accordingly
                    order->size -= buySize;
                    unregisterOrder(buyOrder);
                    buyContainer->pop(limit);
                }
                else
                {

                    // Sell order can absorb the full buy order?

                    
                     if(verbose){
                    std::cout<< "Sold " << order->size << " units at price " <<buyOrder->price <<"."<<std::endl;
                    std::cout<<"\n";
                    }
                    buyContainer->updateOrderAtLimit(buyOrder, limit, buySize - order->size);
                    order->size = 0;
                    break;
                }
            }
            if (order != nullptr && order->size > 0)
            {
                 if(verbose){
                std::cout<< "Sell order only partially filled. Remaining volume: " <<order->size << std::endl;
                 std::cout<< "Remaining sell order added to the order book." << std::endl;
                
                }
                sellContainer->addOrder(order);
                registerOrder(order);
            }
            else{
                if(verbose){
                std::cout<< "Sell order filled." << std::endl;
               
                }
            }
        }
        update();
        if(verbose){
       hfill(width);
        }
    }


    template <typename LimitT, typename LimitContainerT, typename LimitContainerU>
    void OrderBook<LimitT, LimitContainerT, LimitContainerU>::update()
    {
         // Update ask and bids
        if (!sellContainer->isEmpty())
        {
            askPrice = sellContainer->topPrice();
        }
        else
        {
            askPrice = 0;
        }
        if (!buyContainer->isEmpty())
        {

            bidPrice = buyContainer->topPrice();
        }
        else
        {
            bidPrice = 0;
        }
    }





     /**
     * @brief Cancels an order from the order book.
     * @param order to be cancelled
     *  * @param verbose if true, prints which order is cancelled
    */
    template <typename LimitT, typename LimitContainerT, typename LimitContainerU>
    void OrderBook<LimitT, LimitContainerT, LimitContainerU>::cancelOrder(Order *order, bool verbose)
    {
        if (order->orderType == Buy)
        {
             if(verbose){
                std::cout<< "Buy order cancelled. Id: " << order->orderId;
                 std::cout<< ", Price: " << order->price;
                  std::cout<< ", Size: " << order->size<< std::endl;
                  
            }
            unregisterOrder(order);
            buyContainer->deleteOrder(order);
           
        }
        else if (order->orderType == Sell)
        {
            if(verbose){
                std::cout<< "Sell order cancelled. Id: " << order->orderId;
                 std::cout<< ", Price: " << order->price;
                  std::cout<< ", Size: " << order->size<< std::endl;
                
            }
            unregisterOrder(order);
            sellContainer->deleteOrder(order);
        }
        update();
        if(verbose){
            hfill(40);
        }
    }


     /**
     * @brief Adds a new order with specified size, price and order type.
     * @param size the size of the new order
     * @param price the price of the new order
     * @param orderType the type of the order (buy/sell)
     * @param verbose if true, prints which trades are performed
     * @return The new order that was created.
    */
    template <typename LimitT, typename LimitContainerT, typename LimitContainerU>
    Order *OrderBook<LimitT, LimitContainerT, LimitContainerU>::addOrder(int size, int price, OrderType orderType, bool verbose)
    {

        Order *order = new Order(size, price, orderType);
        addOrder(order, verbose);
        return order;
    }



     /**
     * @brief Adds a new order with specified size, price and order type.
     * @param order to be registered in the order book
    */
    template <typename LimitT, typename LimitContainerT, typename LimitContainerU>
    void OrderBook<LimitT, LimitContainerT, LimitContainerU>::registerOrder(Order *order)
    {
            currentId++;
            order->orderId = currentId;
            orderMap[currentId] = order;
           
    }

     /**
     * @brief Adds a new order with specified size, price and order type.
     * @param order to be registered in the order book
    */
    template <typename LimitT, typename LimitContainerT, typename LimitContainerU>
    void OrderBook<LimitT, LimitContainerT, LimitContainerU>::unregisterOrder(Order *order)
    {
        
        if(!orderMap.contains(order->orderId)){return;}
            
            
            orderMap.erase(order->orderId);
            
    }
    




    /*! */
    /**
     * @brief  Center-aligns string within a field of width w. Pads with blank spaces
        to enforce alignment.
     * @param s the string to be formatted
     * @param w the width of the field containing s
     * @return the formatted string
    */
    std::string center(const std::string s, const int w)
    {
        std::stringstream ss, spaces;
        int padding = w - s.size(); // count excess room to pad
        for (int i = 0; i < padding / 2; ++i)
            spaces << " ";
        ss << spaces.str() << s << spaces.str(); // format with padding
        if (padding > 0 && padding % 2 != 0)     // if odd #, add 1 space
            ss << " ";
        return ss.str();
    }



     /**
     * @brief Prints the current order book, and shows how many sell/buy orders exist at which price.
    */
    template <typename LimitT, typename LimitContainerT, typename LimitContainerU>
    void OrderBook<LimitT, LimitContainerT, LimitContainerU>::print()
    {

        //List of all prices, from both buy and sell orders
        std::map<int, std::vector<int>, std::greater<int>> prices;
        for (auto &pair : buyContainer->limits)
        //First enter all buy orders
        {
            int price = pair.first;
            //A price should never be in both limit containers
            assert(!sellContainer->limits.contains(price));
            // if (sellContainer->limits.contains(price))
            // {
            //     //Check if the price is in both limit containers
            //     // Note that that should never happen.
            //     prices[price] = {pair.second->size, sellContainer->limits[price]->size};
            // }
            // else
            // {
             prices[price] = {pair.second->size, 0};
            // }
        }

        for (auto &pair : sellContainer->limits)
        {
            //Now record all sell order prices
            int price = pair.first;
            
                prices[price] = {0, pair.second->size};
        }



        //Start printing the orders
        int numBars = 40;
        bool asks = true;

        hfill(numBars);
        std::cout << "Current status of limit order book " << "\n";
        //Show the spread
        std::cout << "Bid-ask spread: " << spread() << "\n";
        hfill(numBars);
        std::cout << "| " << center("bids", 10) << " | "
                  << center("price", 10) << " | "
                  << center("asks", 10) << " |" << "\n";
        hfill(numBars);
        for (auto &price : prices)
        {
            if (asks == true && price.second[1] == 0)
            {
                asks = false;
                hfill(numBars);
            }
            std::cout << "| ";
            std::stringstream ss;
            if (price.second[0] == 0)
            {
                std::cout << center(" ", 10);
            }
            else
            {
                std::cout << center(std::to_string(price.second[0]), 10);
            }
            std::cout << " | " << center(std::to_string(price.first), 10) << " | ";
            if (price.second[1] == 0)
            {
                std::cout << center(" ", 10);
            }
            else
            {
                std::cout << center(std::to_string(price.second[1]), 10);
            }
            std::cout << " |" << "\n";
        }
        hfill(numBars);
    }



    //Default initialization of template
    template class OrderBook<Limit, LimitContainer<Limit, std::less<int>>, LimitContainer<Limit, std::greater<int>>>;

   
   
    
   


    }

