#include "Book.h"
#include <iostream>
// #include <string>
// class Book
// {

// public:
//     int currentId;
//     LimitTree *buyTree;// contains all buy limit orders
//     LimitTree *sellTree;//containss all sell limit orders, prices are negative, so that
// -sellTree->top() returns the smallest sell price;
// int askPrice;
// int bidPrice;

Book::Book() : currentId(0), buyTree(nullptr), sellTree(nullptr), askPrice(-1), bidPrice(-1)
{
    buyTree = new LimitTree;
    sellTree = new LimitTree;
}

int Book::spread()
{
    return askPrice - bidPrice;
}
void Book::addOrder(Order *order)
{
    if(order==nullptr || order->size ==0 ){ return;}
    if (order->price > 0)
    {

        while (!sellTree->isEmpty()  &&order->size>0&& -sellTree->topPrice() < order->price)
        {
            // There is a matching sell order?
                LimitNode *limit = sellTree->top();

                Order *sellOrder = sellTree->topOrder();
                int sellSize = sellOrder->size;

                if (order->size >= sellSize)
                {
                    //Order size exceeds the first visible?
                    //Then delete the first sell order and reduce the buy order accordingly
                    order->size -= sellSize;
                    sellTree->pop(limit);
                   
                }
                else if (sellSize > order->size)
                {
                    
                    //Sell order can absorb the full buy order?
                    sellTree->updateOrderAtPrice(sellOrder, limit, sellSize-order->size);
                    break;
                }
                
            
            
           
        }
        if(order!=nullptr && order->size >0){
                buyTree->addOrder(order);
                
        }
       
    }
    
    if(order->price < 0)
    {
        // Is sell order?
        

        while (!buyTree->isEmpty() && order->size>0&& -order->price <= buyTree->topPrice())
        {
            // There is a matching buy order?

            
                LimitNode *limit = buyTree->top();

                Order *buyOrder = buyTree->topOrder();
                int buySize = buyOrder->size;

                if (order->size >= buySize)
                {
                   
                    //Order size exceeds the first visible?
                    //Then delete the first sell order and reduce the buy order accordingly
                    order->size -= buySize;
                    buyTree->pop(limit);
                   
                }
                else if (buySize > order->size)
                {
                    
                    //Sell order can absorb the full buy order?
                    
                    buyTree->updateOrderAtPrice(buyOrder, limit, buySize-order->size);
                  
                    break;
                }
                
            
            
           
        }
        if(order!=nullptr && order->size >0){
                sellTree->addOrder(order);
                
        }
    }
    //Update ask and bids
    askPrice = -sellTree->topPrice();
    bidPrice = buyTree->topPrice();
}

void Book::cancelOrder(Order *order)
{
    if (order->price > 0)
    {
        buyTree->deleteOrder(order);
    }
    else
    {
        sellTree->deleteOrder(order);
    }
}

Order *Book::addOrder(int size, int price, std::string orderType)
{
    Order *order;
    if (orderType == "Buy")
    {
        order = new Order(size, price);
    }
    else
    {
        order = new Order(size, -price);
    }
    addOrder(order);
    return order;
}

void Book::explain(){
     std::cout<< "---------------------------------------"<<std::endl;
    std::cout<< "Current state of the limit order book"<<std::endl;
    std::cout<< "---------------------------------------"<<std::endl;
    std::cout << "asks:" << "\n";
    std::cout<< "---------------------------------------"<<std::endl;
    sellTree->explainTree(-1);
    
    std::cout<< "---------------------------------------"<<std::endl;
    std::cout << "bids:" << "\n";
    std::cout<< "---------------------------------------"<<std::endl;
    buyTree->explainTree(1);
    std::cout<< "---------------------------------------"<<std::endl;
    std::cout<< "Bid-ask spread: " << spread()<<std::endl;

}
