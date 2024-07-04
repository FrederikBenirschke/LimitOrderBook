# Limit Order Book

[![Limit order book](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/FrederikBenirschke/LimitOrderBook)


A limit order is a type of order used in financial markets to buy or sell a specific quantity of a security at a specified price or better. It is a fundamental concept in trading where traders can specify the maximum price they are willing to pay when buying or the minimum price they are willing to accept when selling.

The Limit Order Book (LOB) is a crucial component of a trading system. It keeps track of all the outstanding limit orders in the market. The LOB is responsible for organizing and matching these orders based on their specified prices.

When a new limit order arrives, it is compared with the existing orders in the LOB. If there is an existing order with a matching price, the order is filled. The quantity of the incoming order is matched against the existing order. If the incoming order cannot be fully filled, the remaining quantity is added to the LOB.

The order matching process in the LOB  that is implemented here is based on the principle of First-in-first-out (FIFO). This means that the order that has been in the LOB for the longest time is matched first. If there are multiple orders with the same price, the order that was added to the LOB first is matched first.

The LOB ensures that the orders are matched in a fair and efficient manner. It helps maintain the integrity and transparency of the market. Traders can gain insights into market depth and liquidity by monitoring the contents of the LOB.

## Table of Contents

- [Background](#background)
- [Install](#install)
- [Usage](#usage)

- [License](#license)

## Background
A limit order book (LOB) is an integral part of a trading system that facilitates the matching of buy and sell orders. The LOB is responsible for efficiently matching thousands of orders every second, making speed a critical consideration. 

One of the key functionalities of the LOB is the ability to add and cancel orders. When a new order arrives, it is added to the LOB. If an existing order is cancelled, it is removed from the LOB. The LOB must always provide the smallest ask (the highest price at which sellers are willing to sell) and the largest bid (the lowest price at which buyers are willing to buy).

To achieve efficient insertion, deletion, and retrieval of orders in the LOB, a suitable data structure is essential. In this implementation, we use a red-black tree (provided by the std::map container in C++) to store the prices. For each price, we additonally maintain a doubly linked list that stores all the orders at that price.

The red-black tree is a self-balancing binary search tree that ensures efficient search, insertion, and deletion operations. By using a balanced tree, we can quickly find the smallest or largest price in the LOB. The doubly linked list allows for efficient insertion and deletion of orders at a specific price.



## Install

To compile and install the project, follow these steps:

1. Clone the repository:

```bash
git clone https://github.com/FrederikBenirschke/LimitOrderBook.git
```

2. Generate the Makefule using
 [cmake](https://cmake.org)

```bash 
mkdir build
cd build
cmake ..
make
```
 3. Run the executable to start using the Limit Order Book:
```
./LOB
```

Additionally, you can run a benchmark test usin[Google benchmark](https://github.com/google/benchmark). To run the benchmark, execute the following commands:
```
make
./LOB_test
```
The benchmark test involves simulating random order insertions and deletions with varying sizes and prices to assess the efficiency of the Limit Order Book.


## Usage
To utilize the Limit Order Book in your trading system, follow these steps:

```c++
#include "OrderBook.h"
 OrderBook<> book;
 book.addOrder(1, 1, Buy); //Add a buy order to the order book
 //Since it is the first order it will be added directly

 book.addOrder(2, 1, Sell); //add a sell order of size 2 at price 1
 //the order is matched with the existing buy order and one unit is sold
 //the remaining sell order is added to the book
 
 book.print()//the result can be printed

```

If instead of `addOrder(Order* order)` the variant `addOrder(Order* order, bool verbose)` is called, then at every step an explanation of the buys/sells is provided.

Additionally, orders can be cancelled with `cancelOrder(Order* order)`.

More examples can be found in [main](src/main.cpp) and [benchmark](Test/LOBtest.cpp).



An example output of `book.print()` looks as follows
```console
----------------------------------------
Current status of limit order book 
Bid-ask spread: 5
----------------------------------------
|    bids    |   price    |    asks    |
----------------------------------------
|            |     14     |     1      |
|            |     13     |     1      |
|            |     12     |     1      |
|            |     11     |     1      |
|            |     10     |     1      |
----------------------------------------
|     1      |     5      |            |
|     1      |     4      |            |
|     1      |     3      |            |
|     1      |     2      |            |
----------------------------------------
```
 
   








## License

[MIT](LICENSE) © Frederik Benirschke

If you have any further questions, feel free to ask!
Let me know if you need any more information.