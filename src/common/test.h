#ifndef __TEST_H__
#define __TEST_H__

#include <iostream>
#include <assert.h>

#include <iomanip>

#define TEST_PASS() std::cout << "[TEST] " \
                              << std::setw(40) << std::left << __FILE__ << ": PASSED" << std::endl;

#define TEST_FAIL() std::cout << "[TEST] " \
                              << std::setw(40) << std::left << __FILE__ << ": FAILED" << std::endl;

#define TEST_ASSERT(expr)                                        \
    if (!(expr))                                                 \
    {                                                            \
        TEST_FAIL();                                             \
        std::cerr << "Assertion failed: " << #expr << std::endl; \
        std::cerr << "File: " << __FILE__ << std::endl;          \
        std::cerr << "Line: " << __LINE__ << std::endl;          \
        exit(1);                                                 \
    }

// expect an exception
#define TEST_EXPECT_EXCEPTION(expr)                                  \
    try                                                              \
    {                                                                \
        expr;                                                        \
        TEST_FAIL();                                                 \
        std::cerr << "Exception not thrown: " << #expr << std::endl; \
        std::cerr << "File: " << __FILE__ << std::endl;              \
        std::cerr << "Line: " << __LINE__ << std::endl;              \
        exit(1);                                                     \
    }                                                                \
    catch (...)                                                      \
    {                                                                \
        /*do nothing*/                                               \
    }

#endif // __TEST_H__
