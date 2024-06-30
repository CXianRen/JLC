#include "common/jlc_blk.h"
#include "common/test.h"

int main(int argc, char **argv)
{
    {
        JLC::BLK::JLCBlk blk;
        JLC::VAR::JLCVar var1("a", std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::INT));
        JLC::VAR::JLCVar var2("b", std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::DOUB));
        blk.add_var(var1);
        blk.add_var(var2);
        TEST_ASSERT(blk.has_var("a"));
        TEST_ASSERT(blk.has_var("b"));
        TEST_ASSERT(!blk.has_var("c"));
        TEST_ASSERT(blk.get_var("a").name == "a");
        TEST_ASSERT(blk.get_var("b").name == "b");
        TEST_ASSERT(blk.str() == "Block:\n\tint a;\n\tdouble b;\n");
    }
    TEST_PASS();
}