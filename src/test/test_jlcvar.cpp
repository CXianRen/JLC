#include "common/jlc_var.h"
#include "common/test.h"

int main(int argc, char **argv)
{
    {
        auto v = std::make_shared<JLC::VAR::JLCVar>("var_name",
                                                    std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::INT));
        TEST_ASSERT(v->str() == "int var_name;");
    }
    {
        auto v = std::make_shared<JLC::VAR::JLCVar>("var_name",
                                                    std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::DOUB));
        TEST_ASSERT(v->str() == "double var_name;");
    }
    {
        auto v = std::make_shared<JLC::VAR::JLCVar>("var_name",
                                                    std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::BOOL));
        TEST_ASSERT(v->str() == "bool var_name;");
    }
    {
        // custom type
        auto v = std::make_shared<JLC::VAR::JLCVar>("var_name",
                                                    std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::STRUCT, "struct_name"));
        TEST_ASSERT(v->str() == "struct struct_name var_name;");
    }
    {
        // array type
        auto v = std::make_shared<JLC::VAR::JLCVar>("var_name",
                                                    std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::ARRAY,
                                                                                         std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::INT)));
        TEST_ASSERT(v->str() == "int[] var_name;");
    }
    {
        // enum type
        auto v = std::make_shared<JLC::VAR::JLCVar>("var_name",
                                                    std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::ENUM, "enum_name"));
    }

    TEST_PASS();
}