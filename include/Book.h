#ifndef BOOK_H
#define BOOK_H

#include <string>

/**
The order class represents an order in the limit order book. The orders are implemented as doubly linked lists.
This guarantess
     */
class Order
{
public:
    int orderId;
    Order *next;
    Order *prev;
    int size;
    int price;

    /**
     * Standard constructor that creates a new order, sets prize and size to zero by default.
     *
     *
     */
    Order();

    /**
     * Constructor that creates a new order and set the price, size.
     *
     * @param siz is the nummber of shares that should be sold/bought. A positive size indicates a buy order,
     *  a negative price a sell order.
     *  @param pric is the price of the current order.
     */
    Order(int siz, int pric);

    /**
     * Returns true if the size of the order is zero.
     *
     */
    bool isEmpty();

    /**
     * Returns true if the order is a buy order.
     *
     */
    bool isBuy();
};

/**"
The limit class represents a price limit in the otder book. Limits are represented as RB- binary trees.
     */
class LimitNode
{
public:
    int price;
    int size;
    int numOrders;
    LimitNode *left;
    LimitNode *right;
    LimitNode *parent;
    Order *headOrder;
    Order *tailOrder;
    std::string color;
    LimitNode();

    /**
     * Constructor that creates a new limit at a given price.
     *
     * @param price is the price of the limit order.
     */
    LimitNode(int pric);

    /**
     * Standard destructor, deleting every node in the doubly linked order list.
     */
    ~LimitNode();

    /**
     * Returns true if the size of the order is zero.
     *
     */
    bool isEmpty();

    /**
     * Returns true if the order is a buy order.
     *
     */
    bool isBuy();

    void addOrder(Order *newOrder);

    // void updateOrder(Order* order, int newSize);

    Order *top();
    void deleteOrderAtTail();
    void deleteOrder(Order *order);
};

class LimitTree
{

private:
    LimitNode *addLimitHelper(LimitNode *parent, int price, int dir);
    void leftRotate(LimitNode *x);
    void rightRotate(LimitNode *x);
    void fixDelete(LimitNode *x);
    void fixInsertion(LimitNode *k);
    void rbTransplant(LimitNode *u, LimitNode *v);
    void deletePriceHelper(LimitNode *node, int key);
    void inOrderTraversal(LimitNode *node, int factor);

public:
    LimitNode *root;
    LimitNode *NIL;
    int size;
    LimitNode* max;

    LimitTree();

    LimitNode *searchPrice(int price);
    LimitNode *insertPrice(int price);
    void deletePrice(int price);
    void pop(LimitNode *limit);

    void addOrder(Order *order);
    void deleteOrder(Order *order);
    void deleteOrderAtPrice(Order *order, LimitNode *limit);
    void updateOrder(Order *order, int newPrice);
    void updateOrderAtPrice(Order *order, LimitNode *limit, int newPrice);
    LimitNode *top();
    int topPrice();
    Order *topOrder();

    bool isEmpty();
    void explainTree(int factor);
    void levelOrderTraversal();
    LimitNode *minimum(LimitNode *node);
    LimitNode *maximum(LimitNode *node);
};

class Book
{

public:
    int currentId;
    LimitTree *buyTree;  // contains all buy limit orders
    LimitTree *sellTree; // containss all sell limit orders, prices are negative, so that
    // -sellTree->top() returns the smallest sell price;
    int askPrice;
    int bidPrice;
    Book();
    int spread();
    void addOrder(Order *order);
    Order *addOrder(int size, int price, std::string orderType);
    void cancelOrder(Order *order);
    void explain();
};

#endif /* BOOK_H */
