#include <iostream>
#include <cstdlib>
#include <ctime>
#include <random>
#include "OrderBook.h"
using namespace LOB;

#include <benchmark/benchmark.h>

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

// Define a benchmark
// Inserts and deletes orders randomly
static void BM_RandomOrders(benchmark::State &state)
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> buyDis(80, 120);
    std::uniform_int_distribution<> sellDis(90, 140);
    std::uniform_int_distribution<> sizeDis(1, 5);
    OrderBook<> book;
    for (auto _ : state)
    {

        book.addOrder(randomOrder(buyDis, sizeDis, Buy));   // Add a buy order with random size and price
        book.addOrder(randomOrder(sellDis, sizeDis, Sell)); // Add a sell order with random size and price
    }
}



// Define a benchmark
// Inserts and deletes orders randomly
static void BM_RandomOrdersCancel(benchmark::State &state)
{

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> buyDis(90, 100);
    std::uniform_int_distribution<> sellDis(92, 102);
    std::uniform_int_distribution<> sizeDis(1, 5);
    std::uniform_int_distribution<> coin(0, 10);

    OrderBook<> book;
    for (auto _ : state)
    {
        int randomInt = coin(gen);

        if (randomInt <= 4)
        {
            // Add a buy order with random size and price
            book.addOrder(randomOrder(buyDis, sizeDis, Buy));
        }
        else if (randomInt <= 8)
        {
            // Add a sell order with random size and price
            book.addOrder(randomOrder(sellDis, sizeDis, Sell));
        }
        else
        {
            // Randomly cancel orders
            if (!book.orderMap.empty())
            {
                auto it = book.orderMap.begin();
                std::advance(it, rand() % book.orderMap.size());
                int random_key = it->first;
                Order *order = book.orderMap[random_key];
                book.cancelOrder((order));
            }
        }
       
    }
}

// Define a benchmark
// Inserts and deletes orders randomly
static void BM_RandomOrdersBucket(benchmark::State &state)
{
    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> buyDis(80, 120);
    std::uniform_int_distribution<> sellDis(90, 140);
    std::uniform_int_distribution<> sizeDis(1, 5);
    OrderBook<Limit,LimitContainerBucket<Limit>> book;
    for (auto _ : state)
    {

        book.addOrder(randomOrder(buyDis, sizeDis, Buy));   // Add a buy order with random size and price
        book.addOrder(randomOrder(sellDis, sizeDis, Sell)); // Add a sell order with random size and price
    }
}



// Define a benchmark
// Inserts and deletes orders randomly
static void BM_RandomOrdersCancelBucket(benchmark::State &state)
{

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> buyDis(90, 100);
    std::uniform_int_distribution<> sellDis(92, 102);
    std::uniform_int_distribution<> sizeDis(1, 5);
    std::uniform_int_distribution<> coin(0, 10);

    OrderBook<Limit,LimitContainerBucket<Limit>> book;
    for (auto _ : state)
    {
        int randomInt = coin(gen);

        if (randomInt <= 4)
        {
            // Add a buy order with random size and price
            book.addOrder(randomOrder(buyDis, sizeDis, Buy));
        }
        else if (randomInt <= 8)
        {
            // Add a sell order with random size and price
            book.addOrder(randomOrder(sellDis, sizeDis, Sell));
        }
        else
        {
            // Randomly cancel orders
            if (!book.orderMap.empty())
            {
                auto it = book.orderMap.begin();
                std::advance(it, rand() % book.orderMap.size());
                int random_key = it->first;
                Order *order = book.orderMap[random_key];
                book.cancelOrder((order));
            }
        }
       
    }
}

int iter1 = std::pow(10,5);
BENCHMARK(BM_RandomOrders)->Iterations(iter1);
BENCHMARK(BM_RandomOrdersBucket)->Iterations(iter1);
BENCHMARK(BM_RandomOrdersCancel)->Iterations(iter1);
BENCHMARK(BM_RandomOrdersCancelBucket)->Iterations(iter1);


BENCHMARK_MAIN();
