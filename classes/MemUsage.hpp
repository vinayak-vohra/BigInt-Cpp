/**
 * @file MemUsage.hpp
 * @author Vinayak
 * @brief Memory usage of program (not accurate)
 * @version 0.1
 * @date 2022-01-23
 *
 * @copyright Copyright (c) 2022
 *
 */

/*
 ******************* NOTE **********************
 *                                             *
 * Memory usage is based on the use of 'new'   *
 * operator and is not accurate. Actual memory *
 * usage may be higher than shown.             *
 *                                             *
 ***********************************************
 */

#ifndef MemUsage_hpp
#define MemUsage_hpp

#include <stdint.h>
#include <memory>
#include <iostream>
using namespace std;

/**
 * @brief Struct MemUsage to get currently allocated memory
 *
 */
struct MemUsage
{
    uint32_t current_usage;          // current memory usage
    MemUsage() : current_usage(0) {} // initialise
};

// static variable to check mem usage
static MemUsage mem_usage;

/**
 * @brief Overload put to operator for struct MemUsage
 *
 * @param out
 * @param mem
 * @return ostream&
 */
ostream &operator<<(ostream &out, MemUsage &mem)
{
    // Memory > 1024 Bytes
    if (mem.current_usage > 1024)
    {

        double memory = mem.current_usage / 1024.0;

        // Memory in MB
        if (memory > 1024)
        {
            memory /= 1024;
            out << memory << "MB";
        }
        // Memory in KB
        else
            out << memory << "KB";
    }

    // Memory is in Bytes
    else
    {
        out << mem.current_usage << "B";
    }
    return out;
}

/**
 * @brief Overload new operator to save allocated mem usage
 *
 * @param size
 * @return void*
 */
void *operator new(size_t size)
{
    mem_usage.current_usage += size;
    return malloc(size);
}

/**
 * @brief Overload delete operator to remove deallocated mem usage
 *
 * @param mem
 * @param size
 */
void operator delete(void *mem, size_t size)
{
    mem_usage.current_usage -= size;
    free(mem);
}

#endif // MemUsage_hpp