#ifndef __JLC_TYPE_H__
#define __JLC_TYPE_H__

#include <string>
#include <memory>

namespace JLC
{
    namespace TYPE
    {

        enum type_enum
        {
            INT = 0,
            DOUB,
            BOOL,
            VOID,
            CHAR,
            STRING, // user can not define a string type, but we need it

            ENUM,
            STRUCT,
            CLASS,
            ARRAY,
            UNDEFINED
        };

        class JLCType
        {
        public:
            type_enum type;

            // for array
            std::shared_ptr<JLCType> base_type;

            // for custom type like a struct, class, enum
            std::string obj_name;

            //
            JLCType() : type(UNDEFINED){};

            // for basic type
            JLCType(type_enum type) : type(type){};

            // for array
            JLCType(type_enum type,
                    std::shared_ptr<JLCType> base_type) : type(type),
                                                          base_type(base_type){};

            // for struct, class, enum
            JLCType(type_enum type,
                    const std::string &obj_name) : type(type),
                                                   obj_name(obj_name){};

            // copy constructor
            JLCType(const JLCType &t) : type(t.type),
                                        base_type(t.base_type),
                                        obj_name(t.obj_name){};

            std::string str();

            // copy operator
            JLCType &operator=(const JLCType &t)
            {
                type = t.type;
                base_type = t.base_type;
                obj_name = t.obj_name;
                return *this;
            }

            bool operator==(const JLCType &t) const;
            bool operator!=(const JLCType &t) const;
        }; // class JLCType

    } // namespace TYPE
} // namespace JLC

#endif // __JLC_TYPE_H__