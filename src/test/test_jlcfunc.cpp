#include "common/jlc_func.h"
#include "common/test.h"

int main()
{
    {
        // constructor
        JLC::FUNC::JLCFunc f(
            "f",
            std::make_shared<JLC::TYPE::JLCType>(
                JLC::TYPE::type_enum::INT));
        TEST_ASSERT(f.name == "f");
        TEST_ASSERT(f.return_type->type == JLC::TYPE::type_enum::INT);
        // add arg
        f.add_arg(
            JLC::VAR::JLCVar(
                "a",
                std::make_shared<JLC::TYPE::JLCType>(
                    JLC::TYPE::type_enum::INT)));
        f.add_arg(
            JLC::VAR::JLCVar(
                "b",
                std::make_shared<JLC::TYPE::JLCType>(
                    JLC::TYPE::type_enum::DOUB)));
        // is_exist_arg
        TEST_ASSERT(f.is_exist_arg("a"));
        TEST_ASSERT(f.is_exist_arg("b"));
        TEST_ASSERT(!f.is_exist_arg("c"));
        // get_arg
        TEST_ASSERT(f.get_arg("a").name == "a");
        TEST_ASSERT(f.get_arg("b").name == "b");

        // add_block
        f.push_blk();
        f.add_var(
            JLC::VAR::JLCVar(
                "x",
                std::make_shared<JLC::TYPE::JLCType>(
                    JLC::TYPE::type_enum::INT)));
        f.add_var(
            JLC::VAR::JLCVar(
                "y",
                std::make_shared<JLC::TYPE::JLCType>(
                    JLC::TYPE::type_enum::DOUB)));
        // is_exist_var
        TEST_ASSERT(f.is_exist_var("x"));
        TEST_ASSERT(f.is_exist_var("y"));
        TEST_ASSERT(!f.is_exist_var("z"));
        TEST_ASSERT(f.is_exist_var("a"));
        TEST_ASSERT(f.is_exist_var("b"));
        // get_var
        TEST_ASSERT(f.get_var("x").name == "x");
        TEST_ASSERT(f.get_var("y").name == "y");
        TEST_ASSERT(f.get_var("a").name == "a");
        TEST_ASSERT(f.get_var("b").name == "b");

        // insert a new block
        f.push_blk();
        f.add_var(
            JLC::VAR::JLCVar(
                "z",
                std::make_shared<JLC::TYPE::JLCType>(
                    JLC::TYPE::type_enum::BOOL)));
        // is_exist_var
        TEST_ASSERT(f.is_exist_var("z"));
        TEST_ASSERT(f.is_exist_var("x"));
        TEST_ASSERT(f.is_exist_var("y"));
        TEST_ASSERT(f.is_exist_var("a"));
        TEST_ASSERT(f.is_exist_var("b"));
        // get_var
        TEST_ASSERT(f.get_var("z").name == "z");
        TEST_ASSERT(f.get_var("x").name == "x");
        TEST_ASSERT(f.get_var("y").name == "y");
        TEST_ASSERT(f.get_var("a").name == "a");
        TEST_ASSERT(f.get_var("b").name == "b");

        // test str
        std::string s = f.str();
        std::string expected = "Function: f\n"
                               "Return type: int\n"
                               "Arguments:\n"
                               "\t\tint a;\n"
                               "\t\tdouble b;\n"
                               "Blocks:\n"
                               "Block:\n"
                               "\tint x;\n"
                               "\tdouble y;\n"
                               "Block:\n"
                               "\tbool z;\n";
                            
        TEST_ASSERT(s == expected);
        // pop block
        f.pop_blk();
        // is_exist_var
        TEST_ASSERT(!f.is_exist_var("z"));
        TEST_ASSERT(f.is_exist_var("x"));

        // pop block
        f.pop_blk();
        // is_exist_var
        TEST_ASSERT(!f.is_exist_var("x"));
    }
    TEST_PASS();
}