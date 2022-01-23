/**
 * @file BigInt.hpp
 * @author Vinayak Vohra
 * @brief Declarations for BigInt class
 * @version 1
 * @date 2022-01-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef BigInt_hpp
#define BigInt_hpp

#include "Node.hpp" // Node definition
#include <iostream> // for ostream

using namespace std;

/**
 * @brief BigInt stores big numbers as linkedlist
 *
 */
class BigInt
{
    Node *head; // head ptr

public:
    int digit_count;
    BigInt();            // Default constructor
    BigInt(int);         // Initialise with int
    BigInt(string);      // Initialise with string
    BigInt(Node *, int); // Initialise with head ptr
    Node *getHead()      // return head
    {
        return this->head;
    }

    BigInt operator+(BigInt &);                           // Overload add operator
    BigInt operator*(BigInt &);                           // Overload multiply operator
    friend ostream &operator<<(ostream &out, BigInt &bi); // Overload put to operator
};

#endif // BigInt_hpp