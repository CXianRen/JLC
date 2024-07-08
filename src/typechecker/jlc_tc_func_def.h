#ifndef __JLC_TC_current_func_DEF_H__
#define __JLC_TC_current_func_DEF_H__

#include <vector>
#include <string>

#include "common/jlc_operator.h"
#include "common/jlc_context.h"
#include "common/debug.h"

#include "typechecker/jlc_tc_func_dcl.h"

namespace JLC::TC
{
    class JLC_FUNC_DEF_Checker : public JLC_FUNC_CD_Checker
    {
    public:
        JLC_FUNC_DEF_Checker()
            : JLC_FUNC_CD_Checker(),
              current_func_(nullptr){};

        JLC_FUNC_DEF_Checker(
            std::shared_ptr<JLCContext> context)
        {
            context_ = context;
            current_func_ = nullptr;
        };

        ~JLC_FUNC_DEF_Checker() = default;

    public:
        // current function object
        std::shared_ptr<JLC::FUNC::JLCFunc> current_func_;

        void visitFuncDef(FuncDef *p) override;

        // block scope
        void visitBStmt(BStmt *p);

        // declaration variables
        void visitNoInit(NoInit *p) override;
        void visitInit(Init *p) override;
        void visitENewObj(ENewObj *p) override;
        void visitENewBArr(ENewBArr *p) override;
        void visitENewOArr(ENewOArr *p) override;
        
        /* variable access */
        void visitAss(Ass *p) override;

        void visitEVar(EVar *p) override;
        void visitEpropety(Epropety *p) override;
        void visitEArrow(EArrow *p) override;
        
        void visitEAcc(EAcc *p) override;

        /* function */
        void visitEApp(EApp *p) override;
        void visitEFunc(EFunc *p) override;

        /* operator */
        JLC::OP::AddOp g_add_op_;
        JLC::OP::MulOp g_mul_op_;
        JLC::OP::RelOp g_rel_op_;

        void visitPlus(Plus *p) override { g_add_op_ = JLC::OP::AddOp::ADD; }
        void visitMinus(Minus *p) override { g_add_op_ = JLC::OP::AddOp::SUB; }
        void visitTimes(Times *p) override { g_mul_op_ = JLC::OP::MulOp::MUL; }
        void visitDiv(Div *p) override { g_mul_op_ = JLC::OP::MulOp::DIV; }
        void visitMod(Mod *p) override { g_mul_op_ = JLC::OP::MulOp::MOD; }
        void visitLTH(LTH *p) override { g_rel_op_ = JLC::OP::RelOp::LTH; }
        void visitLE(LE *p) override { g_rel_op_ = JLC::OP::RelOp::LE; }
        void visitGTH(GTH *p) override { g_rel_op_ = JLC::OP::RelOp::GTH; }
        void visitGE(GE *p) override { g_rel_op_ = JLC::OP::RelOp::GE; }
        void visitEQU(EQU *p) override { g_rel_op_ = JLC::OP::RelOp::EQU; }
        void visitNE(NE *p) override { g_rel_op_ = JLC::OP::RelOp::NE; }

        void visitEInc(EInc *p) override;   // ++
        void visitEDecr(EDecr *p) override; // --
        void visitENeg(ENeg *p) override;   // -
        void visitENot(ENot *p) override;   // !
        void visitEMul(EMul *p) override;   // x / mod
        void visitEAdd(EAdd *p) override;   // + -
        void visitERel(ERel *p) override;   // > < <= == >= !=
        void visitEAnd(EAnd *p) override;   // &&
        void visitEOr(EOr *p) override;     // ||

        void visitEcast(Ecast *p) override; // ()

        /* condition */
        void visitCond(Cond *p) override;
        void visitCondElse(CondElse *p) override;
        void visitWhile(While *p) override;
        void visitForLoop(ForLoop *p) override;

        /* return */
        bool is_returned_ = false;
        void visitRet(Ret *p) override;
        void visitVRet(VRet *p) override;

        /* expression */
        bool legal_expr_ = false;
        void visitSExp(SExp *p) override;

        /* error handle */
        void visitDecl(Decl *p) override;

    private:
        void checkFuncParams(
            std::shared_ptr<JLC::FUNC::JLCFunc> &func,
            ListExpr *p);

    }; // class JLC_FUNC_DEF_Checker

} // namespace JLC::TC

#endif // __JLC_TC_FUNC_DEF_H__