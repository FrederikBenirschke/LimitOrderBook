#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iterator>
#include "OrderBook.h"
using namespace LOB;


// int main()
// {
//     OrderBook<> book;
//     //Add 9 order at prices from 1 to 9
//     for (int i = 1; i < 10; i++)
//     {
//         book.addOrder(1, i, Buy, true); 
//     }
//     //Show current limit order book
//     book.print();

//     // Add 1 sell order of size 10 at price 1
//     //This should buy all the exisiting buy orders,
//     // and then one sell order will be left overe.
//     book.addOrder(10, 1, Sell, true);
//     book.print();
// }


template <class PriceDis, class SizeDis>
Order *randomOrder(
    PriceDis priceDis, SizeDis sizeDis, OrderType orderType)
{

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

    // std::normal_distribution<int> distribution(mean,std);
    int price = (int)round(priceDis(gen));
    // price can't be negative
    price = std::max(0, price);
    int size = (int)round(sizeDis(gen));
    size = std::max(0, size);

    return new Order(size, price, orderType);
}

int main(){
std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> buyDis(90, 100);
    std::uniform_int_distribution<> sellDis(92, 102);
    std::uniform_int_distribution<> sizeDis(1, 5);
    std::uniform_int_distribution<> coin(0, 10);

    OrderBook<> book;
    for (int i =0; i<500;i++){
    {
        int randomInt =coin(gen);

        if (randomInt <=4)
        {
            // Add a buy order with random size and price
            book.addOrder(randomOrder(buyDis, sizeDis, Buy));
        }
        else if (randomInt  <=8)
        {
            // Add a sell order with random size and price
            book.addOrder(randomOrder(sellDis, sizeDis, Sell));
        }
        else
        {
            // Randomly cancel orders
            if(!book.orderMap.empty()){
            auto it = book.orderMap.begin();
            std::advance(it, rand() % book.orderMap.size());
            int random_key = it->first;
            Order *order = book.orderMap[random_key];
            book.cancelOrder((order));
            }
        }
        book.print();
    }
}
}