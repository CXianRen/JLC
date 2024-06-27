#include "common/jlc_context.h"

#include "common/test.h"

int main(int argc, char **argv)
{
    {
        // add enum
        JLC::CONTEXT::JLCContext ctx;
        std::shared_ptr<JLC::ENUM::JLCEnum>
            e1 = std::make_shared<JLC::ENUM::JLCEnum>("enum_name");
        ctx.add_enum("enum_name", e1);
        TEST_ASSERT(ctx.is_exist_enum("enum_name"));
        TEST_ASSERT(!ctx.is_exist_enum("enum_name2"));
        TEST_ASSERT(ctx.get_enum("enum_name") == e1);
    }
    {
        // add typedef
        JLC::CONTEXT::JLCContext ctx;
        ctx.add_typedef("typedef_struct_ptr_name", "struct_name");
        TEST_ASSERT(ctx.is_exist_typedef("typedef_struct_ptr_name"));
        TEST_ASSERT(!ctx.is_exist_typedef("typedef_struct_ptr_name2"));
        TEST_ASSERT(ctx.get_typedef("typedef_struct_ptr_name") == "struct_name");
    }
    {
        // add struct
        JLC::CONTEXT::JLCContext ctx;
        std::shared_ptr<JLC::STRUCT::JLCStruct>
            s1 = std::make_shared<JLC::STRUCT::JLCStruct>("struct_name");
        ctx.add_struct("struct_name", s1);
        TEST_ASSERT(ctx.is_exist_struct("struct_name"));
        TEST_ASSERT(!ctx.is_exist_struct("struct_name2"));
        TEST_ASSERT(ctx.get_struct("struct_name") == s1);
    }
    {
        // add class
        JLC::CONTEXT::JLCContext ctx;
        std::shared_ptr<JLC::CLASS::JLCClass>
            c1 = std::make_shared<JLC::CLASS::JLCClass>("class_name");
        ctx.add_class("class_name", c1);
        TEST_ASSERT(ctx.is_exist_class("class_name"));
        TEST_ASSERT(!ctx.is_exist_class("class_name2"));
        TEST_ASSERT(ctx.get_class("class_name") == c1);
    }
    {
        // add function
        JLC::CONTEXT::JLCContext ctx;
        std::shared_ptr<JLC::FUNC::JLCFunc>
            f1 = std::make_shared<JLC::FUNC::JLCFunc>(
                "func_name",
                std::make_shared<JLC::TYPE::JLCType>(
                    JLC::TYPE::type_enum::INT));

        ctx.add_func("func_name", f1);
        TEST_ASSERT(ctx.is_exist_func("func_name"));
        TEST_ASSERT(!ctx.is_exist_func("func_name2"));
        TEST_ASSERT(ctx.get_func("func_name") == f1);
    }
    TEST_PASS();
}