#include "context.H"

bool JLCFunc::isExistArg(const std::string &name)
{
    for (const auto &arg : args)
    {
        if (arg.first == name)
        {
            return true;
        }
    }
    return false;
}

bool JLCFunc::isExistVar(const std::string &name)
{
    JLCBLK *temp = blk;
    while (temp)
    {
        if (temp->isExistVar(name))
        {
            return true;
        }
        temp = temp->parent;
    }
    // check if in the arguments
    for (const auto &arg : args)
    {
        if (arg.first == name)
        {
            return true;
        }
    }
    return false;
}

JLCType JLCFunc::getVarType(const std::string &name)
{
    JLCBLK *temp = blk;
    while (temp)
    {
        if (temp->isExistVar(name))
        {
            return temp->JLCVariables[name].type;
        }
        temp = temp->parent;
    }
    // check if in the arguments
    for (const auto &arg : args)
    {
        if (arg.first == name)
        {
            return arg.second;
        }
    }
    return JLCType(UNDEFINED);
}