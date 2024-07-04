#ifndef __JLC_OPERATOR_H__
#define __JLC_OPERATOR_H__
#include <string>

namespace JLC::OP
{
    enum MulOp
    {
        MUL,
        DIV,
        MOD,
    };

    enum AddOp
    {
        ADD,
        SUB
    };

    enum RelOp
    {
        LTH,
        LE,
        GTH,
        GE,
        EQU,
        NE
    };

    std::string str(MulOp op);

    std::string str(AddOp op);

    std::string str(RelOp op);

} // namespace JLC:

#endif // __JLC_OPERATOR_H__