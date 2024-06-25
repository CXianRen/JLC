#ifndef __TEST_H__
#define __TEST_H__

#include <iostream>
#include <assert.h>

#define TEST_PASS() std::cout << "[TEST] " << __FILE__ << ": PASSED" << std::endl;

#define TEST_ASSERT(expr)                                        \
    if (!(expr))                                                 \
    {                                                            \
        std::cerr << "Assertion failed: " << #expr << std::endl; \
        std::cerr << "File: " << __FILE__ << std::endl;          \
        std::cerr << "Line: " << __LINE__ << std::endl;          \
        exit(1);                                                 \
    }

#endif // __TEST_H__
