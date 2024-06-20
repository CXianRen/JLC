/*
    This file contains the implementation of the utility functions.
*/

#ifndef __MMUTIL_H__
#define __MMUTIL_H__

#include "Absyn.H"
#include "iostream"

#define ENABLE_TYPE_CHECK_DEBUG 1

#if DEBUG
#define DEBUG_PRINT(ss) \
    std::cerr << "[DEBUG]:" << ss << std::endl;
#else
#define DEBUG_PRINT(ss)
#endif

#define ERROR_HANDLE(msg)                           \
    while (1)                                       \
    {                                               \
        std::cerr << "ERROR: " << msg << std::endl; \
        exit(1);                                    \
    }

#endif /* __MMUTIL_H__ */