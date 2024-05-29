# Limit Order Book

[![Limit order book](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/FrederikBenirschke/LimitOrderBook)


A limit order is an order to buy a stock at a specified maximum or sell a stock at a fixed minimum price. A limit order book is an integral part of a trading system and keeps track of the outstanding bid and asks, which are cleared, when new limit orders arrive. Here we implement a First-in-first-out (FIFO) limit order book, which matches incoming orders with the order that have been in the order book for the longest time.

## Table of Contents

- [Background](#background)
- [Install](#install)
- [Usage](#usage)

- [License](#license)

## Background
A limit order book is an integral part of a trading system and has to match thousands of orders every second. Hence speed is an important consideration. Orders can be added and cancelled and we always need to know which existing order has the smallest ask/largest bid. It is thus paramount to chose the correct data structure to allow efficient insertion/deletion/max. Here we implement a c++ template of limit order book, which can be implemented using different underlying structures. As an example we use a red-black tree (provided by std::map) to store the prices and for each price we have a doubly linked list storing all orders at a given price.



## Install

After cloning the repository the project can be compiled using
 [cmake](https://cmake.org) as follows

```
mkdir build
cd build
cmake ..
make
./LOB
```

Using [Google benchmark](https://github.com/google/benchmark) we also can perform a benchmark test
via
```
make
./LOB_test
```
The benchmark consist of random insertion/deletion of orders (with random size/prices).

## Usage


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