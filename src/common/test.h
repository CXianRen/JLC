#ifndef __TEST_H__
#define __TEST_H__

#include <iostream>
#include <assert.h>

#include <iomanip>

#define TEST_PASS() std::cout << "[TEST] " \
                              << std::setw(50) << std::left << __FILE__ << ": PASSED" << std::endl;

#define TEST_FAIL() std::cout << "[TEST] " \
                              << std::setw(50) << std::left << __FILE__ << ": FAILED" << std::endl;

#define TEST_ASSERT(expr)                                        \
    if (!(expr))                                                 \
    {                                                            \
        TEST_FAIL();                                             \
        std::cerr << "Assertion failed: " << #expr << std::endl; \
        std::cerr << "File: " << __FILE__ << std::endl;          \
        std::cerr << "Line: " << __LINE__ << std::endl;          \
        exit(1);                                                 \
    }

#define TEST_ASSERT_STR_EQ(str1, str2)                    \
    if (str1 != str2)                                     \
    {                                                     \
        TEST_FAIL();                                      \
        std::cerr << "Assertion failed: "                 \
                  << str1 << " != " << str2 << std::endl; \
        std::cerr << "File: " << __FILE__ << std::endl;   \
        std::cerr << "Line: " << __LINE__ << std::endl;   \
        exit(1);                                          \
    }

#define TEST_ASSERT_INT_EQ(int1, int2)                    \
    if (int1 != int2)                                     \
    {                                                     \
        TEST_FAIL();                                      \
        std::cerr << "Assertion failed: "                 \
                  << int1 << " != " << int2 << std::endl; \
        std::cerr << "File: " << __FILE__ << std::endl;   \
        std::cerr << "Line: " << __LINE__ << std::endl;   \
        exit(1);                                          \
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

#include "parser/Parser.H"
#include "Printer.H"
#include "parser/Absyn.H"
#include "ParserError.H"

Prog *gen_ast(std::string input_str);

extern PrintAbsyn *p;
extern ShowAbsyn *s;

#endif // __TEST_H__
