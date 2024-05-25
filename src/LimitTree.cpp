#include <iostream>
#include <queue>
#include "Book.h"

#define LEFT 0
#define RIGHT 1

// class LimitTree
// {

// private:

LimitNode *LimitTree::addLimitHelper(LimitNode *parent, int price, int dir)
{
    /* Adds a new node which is child of parent. dir=0 inserts a child to the left, dir=1 to the right*/
    LimitNode *newNode = new LimitNode(price);
    newNode->left = NIL;
    newNode->right = NIL;
    newNode->color = "RED";
    if (dir == 0)
    {
        LimitNode *child = parent->left;
        if (child != NIL)
        {

            newNode->left = child;
            child->parent = newNode;
        }
        parent->left = newNode;
        newNode->parent = parent;
    }
    else
    {
        LimitNode *child = parent->right;
        if (child != NIL)
        {

            newNode->right = child;
            child->parent = newNode;
        }
        parent->right = newNode;
        newNode->parent = parent;
    }
    return newNode;
}

void LimitTree::leftRotate(LimitNode *x)
{
    /*
    Changes a configuration
            x
             \
              y
             / \
            a   b
    to
                y
               / \
              x   b
             /
            a

                            */
    LimitNode *y = x->right;
    x->right = y->left;
    if (y->left != NIL)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
        root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void LimitTree::rightRotate(LimitNode *x)
{
    /*
   Changes a configuration
               x
              /
             y
            / \
           a   b
   to
               y
              / \
             a   x
                /
               b

                           */
    LimitNode *y = x->left;
    x->left = y->right;
    if (y->right != NIL)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr)
    {
        root = y;
    }
    else if (x == x->parent->right)
    {
        x->parent->right = y;
    }
    else
    {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void LimitTree::fixInsertion(LimitNode *k)
{
    while (k != root && k->parent->color == "RED")
    {
        // Both k and its parent are red?

        if (k->parent == k->parent->parent->left)
        {
            // Uncle lies to the right?
            LimitNode *u = k->parent->parent->right; // uncle

            // If uncle and parent are red, color both black and make the grandparent red
            // Then move upwards recursivelt
            if (u->color == "RED")
            {
                k->parent->color = "BLACK";
                u->color = "BLACK";
                k->parent->parent->color = "RED";
                k = k->parent->parent;
            }
            else
            {
                // If parent is red, uncle is black?

                if (k == k->parent->right)
                {
                    // If Node is a right child?
                    // Perform a left rotation on the parent, to make it a left child
                    k = k->parent;
                    LimitTree::leftRotate(k);
                }
                // Then perform a right rotation on the grand parent and recolor
                k->parent->color = "BLACK";
                k->parent->parent->color = "RED";
                rightRotate(k->parent->parent);
            }
        }
        else
        {
            // Now deal with the case that the uncle lies to the left
            // Everything stays the same, just the orientation is reversed
            LimitNode *u = k->parent->parent->left; // uncle
            if (u->color == "RED")
            {
                // If uncle and parent are red, color both black and make the grandparent red
                // Then move upwards recursively
                k->parent->color = "BLACK";
                u->color = "BLACK";
                k->parent->parent->color = "RED";
                k = k->parent->parent;
            }
            else
            {
                // If parent is red, uncle is black?
                if (k == k->parent->left)
                {
                    // If Node is a left child?
                    // Perform a right rotation on the parent, to make it a right child
                    k = k->parent;
                    rightRotate(k);
                }
                // Then perform a left rotation on the grand parent and recolor
                k->parent->color = "BLACK";
                k->parent->parent->color = "RED";
                leftRotate(k->parent->parent);
            }
        }
    }
    root->color = "BLACK";
}

// fix the rb tree modified by the delete operation
void LimitTree::fixDelete(LimitNode *x)
{
    /* Fix the coloring of the tree, when x is a black node*/
    LimitNode *s; // sibling
    while (x != root && x->color == "BLACK")
    {

        if (x == x->parent->left)
        {
            s = x->parent->right;
            if (s->color == "RED")
            {
                // Case 1: Sibling is red
                // In  this case, swap the colors of s and x's parent and rotate the parent of x to the left
                //  Since both x.parent and any child of s are black, we have moved to a case where x is black and has a black sibling
                s->color = "BLACK";
                x->parent->color = "RED";
                leftRotate(x->parent);
                s = x->parent->right;
            }

            if (s->left->color == "BLACK" && s->right->color == "BLACK")
            {
                // Case 2: Sibling is black and both children of sibling are also black
                // Recolor s and then move up in height by replacing x with x.parent
                s->color = "RED";
                x = x->parent;
            }
            else
            {
                if (s->right->color == "BLACK")
                {
                    // case 3: Sibling black, left child of S is red, right child of S is black
                    // Swap the colors of the children and rotate to the right, then we land in case 4
                    s->left->color = "BLACK";
                    s->color = "RED";
                    rightRotate(s);
                    s = x->parent->right;
                }

                // Case 4:
                //  Sibling black, left child of S is black, right child of S is red
                // Change the colors of x's parent and s to black and rotate the parent left
                // This resolves the double back
                s->color = x->parent->color;
                x->parent->color = "BLACK";
                s->right->color = "BLACK";
                leftRotate(x->parent);
                x = root;
            }
        }
        else
        {
            // Now everything is mirrored, but otherwise we have the same four cases
            s = x->parent->left;
            if (s->color == "RED")
            {
                // Case 1
                s->color = "BLACK";
                x->parent->color = "RED";
                rightRotate(x->parent);
                s = x->parent->left;
            }

            if (s->right->color == "BLACK" && s->right->color == "BLACK")
            {
                // Case 2
                s->color = "RED";
                x = x->parent;
            }
            else
            {
                if (s->left->color == "BLACK")
                {
                    // Case 3
                    s->right->color = "BLACK";
                    s->color = 1;
                    leftRotate(s);
                    s = x->parent->left;
                }

                // Case 4
                s->color = x->parent->color;
                x->parent->color = "BLACK";
                s->left->color = "BLACK";
                rightRotate(x->parent);
                x = root;
            }
        }
    }
    x->color = "BLACK";
}

void LimitTree::rbTransplant(LimitNode *u, LimitNode *v)
{
    /* Moves the node v to the position of u. */
    if (u->parent == NIL)
    {
        root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void LimitTree::deletePriceHelper(LimitNode *node, int key)
{
    /* Removes the node containing key in the subtree rooted at node.
    Rebalances the tree.*/


    bool newMax= (node==max);
    // First step is to find the node containing key
    LimitNode *z = NIL; // z is used to store that node containing key and will be deleted later
    LimitNode *x, *y;
    while (node != NIL)
    {
        if (node->price == key)
        {
            z = node;
        }

        if (node->price <= key)
        {
            node = node->right;
        }
        else
        {
            node = node->left;
        }
    }

    if (z == NIL)
    {

        return;
    }
    // now we found the node containing z
    //

    y = z;
    std::string yOriginalColor = y->color;
    if (z->left == NIL)
    {
        // z has no left subtree?
        // then move the right tree up
        x = z->right;
        rbTransplant(z, z->right);
    }
    else if (z->right == NIL)
    {
        // z has no right subtree?
        // then move the left tree up
        x = z->left;
        rbTransplant(z, z->left);
    }
    else
    {
        // Need to find the successor of z in the BST

        y = minimum(z->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            rbTransplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        rbTransplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }
    delete z;
    if (yOriginalColor == "BLACK")
    {
        fixDelete(x);
    }

    if (newMax){ max = maximum(root);}

   
}

void LimitTree::inOrderTraversal(LimitNode *node, int factor)
{
    LimitNode *current = node;
    if (current != NIL)
    {
        inOrderTraversal(current->left,factor);
        
        std::cout << "Price: " << factor*current->price <<", Volume:"<< current->size << ", Number of orders: "<< current->numOrders<<std::endl;
        std::cout << "----------------" << "\n";
        inOrderTraversal(current->right,factor);
    }
}

// public:
// LimitNode *root;
// LimitNode *NIL;
// int size;

LimitTree::LimitTree()
{
    NIL = new LimitNode;
    NIL->left = NIL;
    NIL->right = NIL;
    root = NIL;
    max = root;
    size = 0;
}

void LimitTree::levelOrderTraversal()
{
    std::queue<LimitNode *> currentLevel;

    currentLevel.push(root);

    if (root == NIL)
    {
        return;
    }
    int lvlCounter = 0;
    while (!currentLevel.empty())
    {
        int levelSize = currentLevel.size();
        std::cout << "Level: " << lvlCounter++ << std::endl;
        // vector<int> currentValues;
        for (int i = 0; i < levelSize; i++)
        {
            LimitNode *currentNode = currentLevel.front();
            if (currentNode->left != NIL)
            {
                currentLevel.push(currentNode->left);
            }
            if (currentNode->right != NIL)
            {
                currentLevel.push(currentNode->right);
            }
            std::cout << currentNode->price << ", " << currentNode->color << ", ";
            currentLevel.pop();
        }
        std::cout << std::endl;
    }
}

LimitNode *LimitTree::minimum(LimitNode *node)
{
    /* Returns the node with the minimum price in the subtree rooted at node.*/

    while (node != NIL)
    {
        node = node->left;
    }
    return node;
}

LimitNode *LimitTree::maximum(LimitNode *node)
{
    /* Returns the node with the minimum price in the subtree rooted at node.*/

    while (node != NIL)
    {
        node = node->right;
    }
    return node;
}

void LimitTree::deletePrice(int price)
{

    if (root->left == NIL && root->right == NIL)
    {
        root = NIL;max=NIL;
    }
    else
    {
        deletePriceHelper(this->root, price);
    }
}

LimitNode *LimitTree::searchPrice(int price)
{
    LimitNode *current = root;
    while (current != NIL)
    {
        if (current->price == price)
        {
            return current;
        }
        if (current->price < price)
        {

            current = current->right;
        }
        else
        {

            current = current->left;
        }
    }
    return current;
}

void LimitTree::addOrder(Order *order)
{
    LimitNode *limit = insertPrice(order->price);
    limit->addOrder(order);
    size += order->size;
}

void LimitTree::pop(LimitNode *limit)
{
    if (limit == NIL)
    {
        return;
    }
    Order *order = limit->top();
    if (order == nullptr)
    {
        return;
    }
    updateOrderAtPrice(order, limit, 0);
    limit->deleteOrder(order);
    if (limit->isEmpty())
    {
        deletePrice(limit->price);
    }
}

void LimitTree::deleteOrder(Order *order)
{
    LimitNode *limit = searchPrice(order->price);
    if (limit == NIL)
    {
        return;
    }
    updateOrder(order, 0);
    limit->deleteOrder(order);
    if (limit->isEmpty())
    {
        deletePrice(limit->price);
    }
}

void LimitTree::deleteOrderAtPrice(Order *order, LimitNode *limit)
{

    updateOrderAtPrice(order, limit, 0);
    limit->deleteOrder(order);
    if (limit->isEmpty())
    {
        deletePrice(limit->price);
    }
}

void LimitTree::updateOrderAtPrice(Order *order, LimitNode *limit, int newSize)
{

    limit->size += (-order->size + newSize);
    size += (-order->size + newSize);
    order->size = newSize;
}

void LimitTree::updateOrder(Order *order, int newSize)
{
    LimitNode *limit = searchPrice(order->price);

    if (limit == NIL)
    {

        return;
    }

    limit->size += (-order->size + newSize);
    size += (-order->size + newSize);
    order->size = newSize;
}

int LimitTree::topPrice()
{
    if (max == NIL)
    {
        return 0;
    }
    return max->price;
}

Order *LimitTree::topOrder()
{
    
    return max->top();
}

LimitNode *LimitTree::top()
{
    return max;
}

/* searchPricees if the current price is already contained in the limit tree. If not it adds a new node.
 */
LimitNode *LimitTree::insertPrice(int price)
{
    if (root == NIL)
    {
        // Tree is empty?
        // Then add a new node and color it black
        root = new LimitNode(price);
        root->color = "BLACK";
        root->left = NIL;
        root->right = NIL;
        max = root;
        return root;
    }
    LimitNode *parent;
    LimitNode *current = root;
    // First perform standard insertion in a  BinarysearchPriceTree
    while (current != NIL)
    {
        parent = current;
        if (price == parent->price)
        {
            return parent;
        }
        if (price < current->price)
        {
            current = current->left;
        }
        else
        {
            current = current->right;
        }
        
    }

    LimitNode *newNode;
    if (price > parent->price)
    {
        newNode = addLimitHelper(parent, price, 1);
    }
    else
    {
        newNode = addLimitHelper(parent, price, 0);
    }

    // Fix wrong coloring and imbalancing after inserting the node
    fixInsertion(newNode);

    //Change maximum node if necessary
    if (newNode->price > max->price){max = newNode;}
    return newNode;
}

bool LimitTree::isEmpty()
{
    return root == NIL;
}

void LimitTree::explainTree(int factor =1)
{
    inOrderTraversal(root, factor);
}

// int main()
// {
//     LimitTree tree;
//     tree.insertPrice(1);

//     tree.insertPrice(6);

//     for (int i = 0; i < 3; i++)
//     {
//         tree.insertPrice(i);
//     }
//     tree.levelOrderTraversal();
//     // std::cout << tree.root->right->left->right->price << tree.root->right->right->left->price;
//     tree.deletePrice(6);
//     std::cout<< "Deleted" <<std::endl;
//     tree.levelOrderTraversal();
//     // std::cout<< tree.root->right->price;
// }