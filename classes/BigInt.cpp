/**
 * @file BigInt.cpp
 * @author Vinayak
 * @brief BigInt class member function definitions
 * @version 1
 * @date 2022-01-23
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "BigInt.hpp"
#include "MemUsage.hpp"
#include <algorithm>

// ******************** Constructors ******************** //
// Default Constructor
/**
 * @brief Construct a new Big Int:: Big Int object
 *
 */
BigInt::BigInt()
{
    this->head = nullptr;
    this->digit_count = 0;
}

// Integer Constructor
/**
 * @brief Construct a new Big Int:: Big Int object from Integer value
 *
 * @param number number to store in BigInt
 */
BigInt::BigInt(int number)
{

    int count = 1;
    int mod = number % 10; // get last digit
    number /= 10;          // update number

    /**
     * 1. create node
     * [1]->nullptr
     *
     * 2. update head & tail
     * [1]->nullptr
     * (H)/(T)
     *
     */
    Node *node = new Node(mod);
    Node *tail = node;
    this->head = node;

    // Loop while number has digits
    while (number)
    {
        int mod = number % 10;
        number /= 10;

        /* [0]->[1]->nullptr
         * (H)  (T)
         *
         * 1. create node:
         * [2]->nullptr
         *
         * 2. update tail->next
         * [0]->[1]
         * (H)  (T)->[2]->nullptr
         *
         * 3. update tail
         * [0]->[1]->[2]->nullptr
         * (H)       (T)
         */

        Node *node = new Node(mod);
        tail->next = node;
        tail = node;
        count++;
    }
    this->digit_count = count;
}

// String Constructor
/**
 * @brief Construct a new Big Int:: Big Int object from String value
 *
 * @param s string of integers
 * @throws invalid_argument string: (0-9)
 * @throws bad_alloc run-time error if out of memory
 */
BigInt::BigInt(string s)
{
    int count = 0;
    Node *tail = nullptr;

    reverse(s.begin(), s.end()); // reverse the string

    // Iterate and store all digits
    for (char c : s)
    {
        int char_to_int = c; // convert to int
        char_to_int -= 48;   // get actual value

        // Throw error if Out of Memory
        try
        {
            if (char_to_int < 0 || char_to_int > 9)
            {
                string msg = "Invalid integer: '";
                msg += c;
                msg.append("' in input.");
                throw invalid_argument(msg);
            }

            Node *node = new Node(char_to_int); // create Node
            if (!count)
            {
                this->head = node; // update head pointer
                tail = node;
            }
            else
            {
                tail->next = node; // add node at end
                tail = node;       // update tail
            }
        }
        catch (invalid_argument i)
        {
            cout << "\nError: " << i.what();
        }
        catch (bad_alloc b)
        {
            cout << "\nError: Out of memory";
        }
        count++;
    }
    this->digit_count = count; // update digit count
}

// Pointer Constructor
/**
 * @brief Construct a new Big Int:: Big Int object from Head Node ptr
 *
 * @param start pointer to start
 */
BigInt::BigInt(Node *start, int count)
{
    this->head = start;
    this->digit_count = count;
}
////////////////////////////// END CONSTRUCTORS //////////////////////////////

// Utility function for output operator
/**
 * @brief Print BigInt
 *
 * @param out ostream object
 * @param ptr pointer to current node
 */
void print(ostream &out, Node *ptr)
{
    if (ptr == nullptr)
        return;
    print(out, ptr->next);
    out << unsigned(ptr->digit);
}

// ******************** Operator Overloading ******************** //
// Put to (<<) Operator
/**
 * @brief Overload put to operator for BigInt
 *
 * @param out ostream object
 * @param b BigInt object
 * @return ostream&
 */
ostream &operator<<(ostream &out, BigInt &b)
{
    Node *temp = b.getHead();
    print(out, temp);
    return out;
}

// Add (+) Operator
/**
 * @brief Add two BigInt objects
 *
 * @param B BigInt
 * @return BigInt
 */
BigInt BigInt::operator+(BigInt &B)
{
    // Create head & tail pointers
    Node *head = nullptr;
    Node *tail = nullptr;

    // Create temp headers for two BigInt objects
    Node *tempHead1 = this->head;
    Node *tempHead2 = B.getHead();

    int carry = 0; // carry if num > 9
    int count = 0; // count digits in calculated sum

    // Iterate till any one BigInt reaches end
    while (tempHead1 != nullptr && tempHead2 != nullptr)
    {
        // Calculations
        int sum = tempHead1->digit + tempHead2->digit + carry;
        carry = sum / 10;
        sum %= 10;

        Node *node = new Node(sum); // Create Node

        if (head == nullptr)
        {
            head = tail = node; // update head & tail, if null
        }
        else
        {
            tail->next = node; // add new node at end
            tail = node;       // shift end
        }

        tempHead1 = tempHead1->next;
        tempHead2 = tempHead2->next;
        count++;
    }

    // Iterate through left digits
    while (tempHead1 != nullptr)
    {
        int sum = tempHead1->digit + carry;
        carry = sum / 10;
        sum %= 10;

        Node *node = new Node(sum);
        tail->next = node;
        tail = node;
        tempHead1 = tempHead1->next;

        count++;
    }

    // Iterate through left digits
    while (tempHead2 != nullptr)
    {
        int sum = tempHead2->digit + carry;
        carry = sum / 10;
        sum %= 10;

        Node *node = new Node(sum);
        tail->next = node;
        tail = node;
        tempHead2 = tempHead2->next;

        count++;
    }

    // Add carry
    if (carry)
    {
        Node *node = new Node(1);
        tail->next = node;
        tail = node;
        count++;
    }

    // Create BigInt from head and return itF
    BigInt temp(head, count);
    return temp;
}

// Multiply (*) Operator
/**
 * @brief Multiply two BigInt Objects
 *
 * @param b BigInt
 * @return BigInt
 */
BigInt BigInt::operator*(BigInt &b)
{
    // Save head in temp
    Node *temp_current = this->head;

    // Initialise head and tail for list 1
    Node *head_num_1 = nullptr;
    Node *tail_num_1 = nullptr;

    // Initialise head tail and temp_head for list 1
    Node *head_num_2 = nullptr;
    Node *temp_head_num_2 = nullptr;
    Node *tail_num_2 = nullptr;

    int three_way_switch; // for three cases
    int count = 0;        // count digits

    // Iterate through all digits in BigInt 1
    while (temp_current != nullptr)
    {
        int carry = 0;                       // reinitialise carry for each loop
        Node *temp_multiplier = b.getHead(); // save head 2

        /**
         * If head_1 = null:
         *    three_way_switch = 0
         *
         * Else if head_2 = null:
         *    three_way_switch = 1
         *
         * Else:
         *    three_way_switch = -1
         *
         *
         ********* Working *********
         *
         * 1. three_way_switch = 0
         *    -> add nodes in head_1
         *
         * 2. three_way_switch = 1
         *    -> add nodes in head_2
         *
         * 3. three_way_switch = -1
         *    -> add head_2 nodes inside head_1
         *    -> update head_2 nodes with new values
         *
         */

        if (head_num_1 == nullptr)
            three_way_switch = 0;

        else if (head_num_2 == nullptr)
        {
            /**
             * Append 0 Node at start to
             * simulate multiply by 10.
             *
             */
            Node *node = new Node(0);
            head_num_2 = temp_head_num_2 = tail_num_2 = node;
            three_way_switch = 1;
        }

        else
        {
            three_way_switch = -1;

            // Convert Lists into BigInt to add them.
            BigInt n1(head_num_1, 0);
            BigInt n2(head_num_2, 0);
            BigInt n3 = n1 + n2;

            // save the head ptr of BigInt in head of list 1
            head_num_1 = n3.getHead();

            /**
             * Append 0 Node at start to
             * simulate multiply by 10.
             *
             */
            tail_num_2 = temp_head_num_2;
            tail_num_2 = tail_num_2->next;

            Node *node = new Node(0, tail_num_2);
            temp_head_num_2->next = node;
            temp_head_num_2 = temp_head_num_2->next;
        }

        // Iterate through each digit of BigInt 2
        while (temp_multiplier != nullptr)
        {
            // calculations
            int product = temp_current->digit * temp_multiplier->digit + carry;
            carry = product / 10;
            product %= 10;

            // Use three_way_switch to check
            // which node should be selected
            // to add new values
            switch (three_way_switch)
            {
                // Save in List 1
                // -> used for 1-digit multiplication
            case 0:
            {
                Node *node = new Node(product); // create node

                if (head_num_1 == nullptr)
                {
                    head_num_1 = tail_num_1 = node; // update head ptr
                }
                else
                {
                    tail_num_1->next = node; // add new node at end
                    tail_num_1 = node;       // update end
                }
                count++;
                break;
            }

                // Save in List 2
                // -> used when digits > 1
            case 1:
            {
                Node *node = new Node(product); // create node
                tail_num_2->next = node;        // add new node at end
                tail_num_2 = node;              // update end
            }
            break;

                // This case is used for memory efficient code
                // -> used when digits > 2

                // Instead of creating a new List,
                // Add List 2 into List 1
                // And now update List 2 values when needed
            case -1:
                tail_num_2->digit = product;   // update current tail
                tail_num_2 = tail_num_2->next; // move tail ptr
                break;
            }

            temp_multiplier = temp_multiplier->next;
        }

        // Also, not forget the carry
        if (carry)
        {
            Node *node = new Node(carry);

            // Add in List 1
            if (!three_way_switch)
            {
                tail_num_1->next = node;
                tail_num_1 = node;
                count++;
            }

            // Add in List 2
            else if (three_way_switch == 1)
            {
                tail_num_2->next = node;
                tail_num_2 = node;
            }

            // Update in List 2
            else
            {
                tail_num_2->digit = carry;
                tail_num_2 = tail_num_2->next;
            }
        }
        temp_current = temp_current->next;
    }

    // Return BigInt if only 1-digit
    if (!three_way_switch)
    {
        BigInt temp(head_num_1, count);
        return temp;
    }

    // Add list 1 and 2 if digits > 1
    else
    {
        BigInt n1(head_num_1, 0);
        BigInt n2(head_num_2, 0);
        BigInt n3 = n1 + n2;
        return n3;
    }
}