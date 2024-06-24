#ifndef __JLC_ENUM_H__
#define __JLC_ENUM_H__

#include <string>
#include <vector>

namespace JLC::ENUM
{
    class JLCEnum
    {
    public:
        std::string obj_name;
        std::vector<std::pair<std::string, int>> members;

        JLCEnum(const std::string &name) : obj_name(name){};

        void add_member(const std::string &name);

        bool has_member(const std::string &name);
        
        int get_member_value(const std::string &name);

        std::string str();
    };

} // namespace JLC::ENUM

#endif // __JLC_ENUM_H__