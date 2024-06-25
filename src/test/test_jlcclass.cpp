#include "common/jlc_class.h"
#include "common/test.h"

int main(int argc, char **argv){
    {
        auto c = std::make_shared<JLC::CLASS::JLCClass>("class_name");
        c->add_member("member1", std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::INT));
        c->add_member("member2", std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::DOUB));
        c->add_member("member3", std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::BOOL));
        TEST_ASSERT(c->str() == "class class_name {\n    int member1;\n    double member2;\n    bool member3;\n};\n");
    }
    {
        // array member
        auto c = std::make_shared<JLC::CLASS::JLCClass>("class_name");
        c->add_member("member1", std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::ARRAY, std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::INT)));
        TEST_ASSERT(c->str() == "class class_name {\n    int[] member1;\n};\n");
    }
    {
        // struct member
        auto c = std::make_shared<JLC::CLASS::JLCClass>("class_name");
        c->add_member("member1", std::make_shared<JLC::TYPE::JLCType>(JLC::TYPE::STRUCT, "struct_name"));
        TEST_ASSERT(c->str() == "class class_name {\n    struct struct_name member1;\n};\n");
    }
    TEST_PASS();
}