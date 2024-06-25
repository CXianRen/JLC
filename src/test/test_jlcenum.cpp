#include "common/jlc_enum.h"

#include "common/test.h"

int main(int argc, char **argv)
{
    {
        JLC::ENUM::JLCEnum e1("enum_name");
        e1.add_member("member1");
        e1.add_member("member2");
        e1.add_member("member3");
        TEST_ASSERT(e1.has_member("member1"));
        TEST_ASSERT(e1.has_member("member2"));
        TEST_ASSERT(e1.has_member("member3"));
        TEST_ASSERT(!e1.has_member("member4"));
        TEST_ASSERT(e1.get_member_value("member1") == 0);
        TEST_ASSERT(e1.get_member_value("member2") == 1);
        TEST_ASSERT(e1.get_member_value("member3") == 2);
        TEST_ASSERT(e1.str() == "enum enum_name {\n    member1 = 0,\n    member2 = 1,\n    member3 = 2,\n};\n");
    }
    TEST_PASS();
}