#include "common/jlc_struct.h"

#include "common/test.h"

#include <cassert>
#include <iostream>

int main(int argc, char **argv)
{
    {
        auto s =
            std::make_shared<
                JLC::STRUCT::JLCStruct>("struct_name");
        s->add_member("member1",
                      std::make_shared<
                          JLC::TYPE::JLCType>(JLC::TYPE::INT));
        s->add_member("member2",
                      std::make_shared<
                          JLC::TYPE::JLCType>(JLC::TYPE::DOUB));
        s->add_member("member3",
                      std::make_shared<
                          JLC::TYPE::JLCType>(JLC::TYPE::BOOL));
        assert(s->str() == "struct struct_name {\n"
                           "    int member1;\n"
                           "    double member2;\n"
                           "    bool member3;\n"
                           "};\n");
    }
    {
        // array member
        auto s =
            std::make_shared<
                JLC::STRUCT::JLCStruct>("struct_name");
        s->add_member("member1",
                      std::make_shared<
                          JLC::TYPE::JLCType>(JLC::TYPE::ARRAY,
                                              std::make_shared<
                                                  JLC::TYPE::JLCType>(JLC::TYPE::INT)));
        assert(s->str() == "struct struct_name {\n"
                            "    int[] member1;\n"
                            "};\n");
    }
    {
        // struct member
        auto s =
            std::make_shared<
                JLC::STRUCT::JLCStruct>("struct_name");
        s->add_member("member1",
                      std::make_shared<
                          JLC::TYPE::JLCType>(JLC::TYPE::STRUCT,
                                              "struct_name"));
        assert(s->str() == "struct struct_name {\n"
                            "    struct struct_name member1;\n"
                            "};\n");
    }
    {
        // test get_member_type
        auto s =
            std::make_shared<
                JLC::STRUCT::JLCStruct>("struct_name");
        s->add_member("member1",
                      std::make_shared<
                          JLC::TYPE::JLCType>(JLC::TYPE::INT));
        s->add_member("member2",
                        std::make_shared<
                            JLC::TYPE::JLCType>(JLC::TYPE::DOUB)); 
        assert(s->get_member_type("member1")->type == JLC::TYPE::INT);
        assert(s->get_member_type("member2")->type == JLC::TYPE::DOUB);
        
    }
    TEST_PASS();
}
