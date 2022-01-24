/**
 * @file Node.hpp
 * @author Vinayak Vohra
 * @brief Contains Node Structure
 * @version 1
 * @date 2022-01-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef Node_hpp
#define Node_hpp
#include <iostream>
#include <stdexcept> // to throw invalid_argument
using namespace std;

/**
 * @brief Structure to store a digit and next ptr
 *
 */
struct Node
{
    uint8_t digit; // Store the digit: 0-9
    Node *next;    // pointer to next Node

    // Constructors
    Node();            // default
    Node(int);         // Initialise digit
    Node(int, Node *); // Initialise both variables
};

// ******************** Node Definitions ******************** //
/**
 * @brief Construct a new Node:: Node object
 *
 */
Node::Node()
{
    this->digit = 0;
    this->next = nullptr;
}

/**
 * @brief Construct a new Node:: Node object
 *
 * @param digit Initialise digit
 * @throws invalid_argument if digit > 9
 */
Node::Node(int digit)
{
    try
    {
        if (digit > 9)
            throw invalid_argument("Expected value < 10, but received " + to_string(digit));

        this->digit = digit;
        this->next = nullptr;
    }
    catch (invalid_argument i)
    {
        cout << "\nError: " << i.what();
    }
}

/**
 * @brief Construct a new Node:: Node object
 *
 * @param digit Initialise digit
 * @param next Initialise next ptr
 * @throws invalid_argument if digit > 9
 */
Node::Node(int digit, Node *next)
{
    try
    {
        if (digit > 9)
            throw invalid_argument("Expected value < 10, but received " + to_string(digit));

        this->digit = digit;
        this->next = next;
    }
    catch (invalid_argument i)
    {
        cout << "\nError: " << i.what();
    }
}

#endif // Node_hpp