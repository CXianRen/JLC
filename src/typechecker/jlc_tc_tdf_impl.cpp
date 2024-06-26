#include "jlc_tc_tdf.h"
#include "jlc_tc_error.h"

namespace JLC::TC
{
    void JLCTopDefinitionChecker::visitEnum(Enum *enum_)
    {
        // get the enum name
        std::string enum_name = enum_->ident_;

        // check if the enum has a list of enum values
        if (context_->is_exist_enum(enum_name))
        {
            // error: enum already defined
            throw JLCTCError("Enum already defined: " + enum_name);
        }

        // create a new enum
        auto enum_obj = std::make_shared<JLCEnum>(enum_name);

        if (enum_->listeval_)
        {
            auto &list_e_val = enum_->listeval_;
            for (ListEVal::iterator i = list_e_val->begin();
                 i != list_e_val->end();
                 ++i)
            {
                std::string enum_val = 
                    static_cast<EnumValue*>(*i)->ident_;
                
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
        // add the enum to the context
        context_->add_enum(enum_name, enum_obj);
    }
} // namespace JLC::TC