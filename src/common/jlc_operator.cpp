#include "common/jlc_operator.h"

namespace JLC::OP
{

    std::string str(MulOp op)
    {
        switch (op)
        {
        case MUL:
            return "*";
        case DIV:
            return "/";
        case MOD:
            return "%";
        default:
            return "undefined";
        }
    }

    std::string str(AddOp op)
    {
        switch (op)
        {
        case ADD:
            return "+";
        case SUB:
            return "-";
        default:
            return "undefined";
        }
    }

    std::string str(RelOp op)
    {
        switch (op)
        {
        case LTH:
            return "<";
        case LE:
            return "<=";
        case GTH:
            return ">";
        case GE:
            return ">=";
        case EQU:
            return "==";
        case NE:
            return "!=";
        default:
            return "undefined";
        }
    }

} // namespace JLC::OP