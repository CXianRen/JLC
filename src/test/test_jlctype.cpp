#include "common/jlc_type.h"

#include <cassert>
#include <iostream>

#include "common/test.h"

int main(int argc, char **argv)
{
    {
        JLC::TYPE::JLCType t1(JLC::TYPE::INT);
        assert(t1.str() == "int");
    }
    {
        JLC::TYPE::JLCType t1(JLC::TYPE::DOUB);
        assert(t1.str() == "double");
    }
    {
        JLC::TYPE::JLCType t1(JLC::TYPE::BOOL);
        assert(t1.str() == "bool");
    }
    {
        JLC::TYPE::JLCType t1(JLC::TYPE::VOID);
        assert(t1.str() == "void");
    }
    {
        JLC::TYPE::JLCType t1(JLC::TYPE::ENUM, "enum_name");
        assert(t1.str() == "enum enum_name");
    }
    {
        JLC::TYPE::JLCType t1(JLC::TYPE::STRUCT, "struct_name");
        assert(t1.str() == "struct struct_name");
    }
    {
        JLC::TYPE::JLCType t1(JLC::TYPE::CLASS, "class_name");
        assert(t1.str() == "class class_name");
    }
    {
        JLC::TYPE::JLCType t1(JLC::TYPE::ARRAY, std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::INT));
        assert(t1.str() == "int[]");
    }
    {
        JLC::TYPE::JLCType t1(JLC::TYPE::UNDEFINED);
        assert(t1.str() == "undefined");
    }
    {
        JLC::TYPE::JLCType t1(JLC::TYPE::ARRAY, std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::INT));
        JLC::TYPE::JLCType t2(JLC::TYPE::ARRAY, std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::INT));
        assert(t1 == t2);
    }
    {
        JLC::TYPE::JLCType t1(JLC::TYPE::ARRAY, std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::INT));
        JLC::TYPE::JLCType t2(JLC::TYPE::ARRAY, std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::DOUB));
        assert(t1 != t2);
    }
    {
        JLC::TYPE::JLCType t1(JLC::TYPE::ARRAY, std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::INT));
        JLC::TYPE::JLCType t2(JLC::TYPE::ARRAY, std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::UNDEFINED));
        assert(t1 != t2);
    }
    {
        // multidimensional array
        JLC::TYPE::JLCType t1(
            JLC::TYPE::ARRAY, 
            std::make_shared<JLC::TYPE::JLCType>(
                JLC::TYPE::ARRAY, 
                std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::INT)
                )
        );
        assert(t1.str() == "int[][]");
    }
    {
        // multidimensional array
        JLC::TYPE::JLCType t1(
            JLC::TYPE::ARRAY, 
            std::make_shared<JLC::TYPE::JLCType>(
                JLC::TYPE::ARRAY, 
                std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::INT)
                )
        );
        JLC::TYPE::JLCType t2(
            JLC::TYPE::ARRAY, 
            std::make_shared<JLC::TYPE::JLCType>(
                JLC::TYPE::ARRAY, 
                std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::INT)
                )
        );
        assert(t1 == t2);
    }
    {
        // multidimensional array
        JLC::TYPE::JLCType t1(
            JLC::TYPE::ARRAY, 
            std::make_shared<JLC::TYPE::JLCType>(
                JLC::TYPE::ARRAY, 
                std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::INT)
                )
        );
        JLC::TYPE::JLCType t2(
            JLC::TYPE::ARRAY, 
            std::make_shared<JLC::TYPE::JLCType>(
                JLC::TYPE::ARRAY, 
                std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::DOUB)
                )
        );
        assert(t1 != t2);
    }
    {
        // struct array
        JLC::TYPE::JLCType t1(
            JLC::TYPE::ARRAY, 
            std::make_shared<JLC::TYPE::JLCType>(
                JLC::TYPE::STRUCT, 
                "struct_name"
                )
        );
        assert(t1.str() == "struct struct_name[]");
    }
    {
        // struct array
        JLC::TYPE::JLCType t1(
            JLC::TYPE::ARRAY, 
            std::make_shared<JLC::TYPE::JLCType>(
                JLC::TYPE::STRUCT, 
                "struct_name"
                )
        );
        JLC::TYPE::JLCType t2(
            JLC::TYPE::ARRAY, 
            std::make_shared<JLC::TYPE::JLCType>(
                JLC::TYPE::STRUCT, 
                "struct_name"
                )
        );
        assert(t1 == t2);
    }
    {
        // struct array
        JLC::TYPE::JLCType t1(
            JLC::TYPE::ARRAY, 
            std::make_shared<JLC::TYPE::JLCType>(
                JLC::TYPE::STRUCT, 
                "struct_name"
                )
        );
        JLC::TYPE::JLCType t2(
            JLC::TYPE::ARRAY, 
            std::make_shared<JLC::TYPE::JLCType>(
                JLC::TYPE::STRUCT, 
                "struct_name2"
                )
        );
        assert(t1 != t2);
    }
    {
        // multidimensional struct array
        JLC::TYPE::JLCType t1(
            JLC::TYPE::ARRAY, 
            std::make_shared<JLC::TYPE::JLCType>(
                JLC::TYPE::ARRAY, 
                std::make_shared<JLC::TYPE::JLCType>(
                    JLC::TYPE::STRUCT, 
                    "struct_name"
                    )
                )
        );
        assert(t1.str() == "struct struct_name[][]");
    }

    TEST_PASS();
}
