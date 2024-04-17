#include "context.H"

JLCContext::JLCContext()
{
    // internal functions
    {
        addFunc("printInt");
        auto &frame = getFunc("printInt");
        frame.returnType = JLCType(VOID);
        frame.addArg("a", JLCType(INT));
    }
    {
        addFunc("printDouble");
        auto &frame = getFunc("printDouble");
        frame.returnType = JLCType(VOID);
        frame.addArg("a", JLCType(DOUB));
    }
    {
        addFunc("printString");
        auto &frame = getFunc("printString");
        frame.returnType = JLCType(VOID);
        frame.addArg("a", JLCType(STRING));
    }
    {
        addFunc("readInt");
        auto &frame = getFunc("readInt");
        frame.returnType = JLCType(INT);
    }
    {
        addFunc("readDouble");
        auto &frame = getFunc("readDouble");
        frame.returnType = JLCType(DOUB);
    }
}