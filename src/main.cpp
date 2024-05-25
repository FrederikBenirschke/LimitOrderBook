#include <iostream>
#include "Book.h"

int main()
{
    Book book;
    LimitTree *tree = book.buyTree;
    // LimitNode *limit = tree->insertPrice(5);
    // std::cout << limit->price;
    // std::cout << book.sellTree->isEmpty() << std::endl;

     book.addOrder(5,1, "Buy");
    book.addOrder(5,2, "Buy");
     
   
//         book.addOrder(1,1, "Buy");
book.explain();
// std::cout<< book.buyTree->top()->price;
// // std::cout<< (book.buyTree->searchPrice(1)== book.buyTree->NIL);
            // book.addOrder(2,3, "Sell");
            // book.explain();
            // book.buyTree->explainTree();
//     // LimitNode*  limit= book.buyTree->top();
//     // // book.buyTree->deletePrice(1);
//     // // std::cout<< "expl";
//     book.buyTree->explainTree();
//     // book.buyTree->pop(limit);
    // std::cout<< limit->isEmpty();
    //  book.buyTree->explainTree();
    // std::cout<< "Got here";
    // Order* order = new Order(1,-1);
    //   book.addOrder(order);
    //   LimitNode* limit = book.sellTree->top();
    // std::cout<< limit->price;
    // book.sellTree->pop(limit);
    // std::cout<< book.sellTree->isEmpty();
    // // std::cout<< order->prev->next->price;
    //   book.sellTree->pop(limit);
    // for (int i=0;i<5;i++){
    //     book.addOrder(i,i, "Buy");
    // }

   
    return 0;
}