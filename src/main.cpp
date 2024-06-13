#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <iterator>
#include "OrderBook.h"
using namespace LOB;


int main()
{
    OrderBook<> book;
    //Add 9 order at prices from 1 to 9
    for (int i = 1; i < 10; i++)
    {
        book.addOrder(1, i, Buy, true); 
    }
    //Show current limit order book
    book.print();

    // Add 1 sell order of size 10 at price 1
    //This should buy all the exisiting buy orders,
    // and then one sell order will be left overe.
    book.addOrder(10, 1, Sell, true);

     for (int i = 1; i < 10; i++)
    {
         book.addOrder(1, i+5, Sell); 
        book.addOrder(1, i, Buy); 
    }
    book.print();
}


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
