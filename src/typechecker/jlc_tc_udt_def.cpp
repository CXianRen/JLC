#include "typechecker/jlc_tc_udt_def.h"

namespace JLC::TC
{
    void JLC_TC_UDT_DEF_Checker::visitEnum(Enum *enum_)
    {
        // enum name
        std::string enum_name = enum_->ident_;

        // get enum object
        auto enum_obj = context_->get_enum(enum_name);

        // add the enum object to the context
        if (enum_->listeval_)
        {
            auto &list_e_val = enum_->listeval_;
            for (ListEVal::iterator i = list_e_val->begin();
                 i != list_e_val->end();
                 ++i)
            {
                // DEBUG_PRINT("Enum value: " << static_cast<EnumValue *>(*i)->ident_);
                std::string enum_val =
                    static_cast<EnumValue *>(*i)->ident_;

                // check if the enum value is already defined
                if (enum_obj->has_member(enum_val))
                {
                    // error: enum value already defined
                    throw JLCTCError("Enum value already defined: " + enum_val);
                }

                // add the enum value to the enum object
                enum_obj->add_member(enum_val);
            }
        }
    }
} // namespace JLC::TC