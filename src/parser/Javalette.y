/* -*- c++ -*- File generated by the BNF Converter (bnfc 2.9.4). */

/* Parser definition to be used with Bison. */

/* Generate header file for lexer. */
%defines "Bison.H"

/* Reentrant parser */
%pure_parser
  /* From Bison 2.3b (2008): %define api.pure full */
%lex-param   { yyscan_t scanner }
%parse-param { yyscan_t scanner }

/* Turn on line/column tracking in the javalette_lloc structure: */
%locations

/* Argument to the parser to be filled with the parsed tree. */
%parse-param { YYSTYPE *result }

%{
/* Begin C preamble code */

#include <algorithm> /* for std::reverse */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Absyn.H"

#define YYMAXDEPTH 10000000

/* The type yyscan_t is defined by flex, but we need it in the parser already. */
#ifndef YY_TYPEDEF_YY_SCANNER_T
#define YY_TYPEDEF_YY_SCANNER_T
typedef void* yyscan_t;
#endif

typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE javalette__scan_string(const char *str, yyscan_t scanner);
extern void javalette__delete_buffer(YY_BUFFER_STATE buf, yyscan_t scanner);

extern void javalette_lex_destroy(yyscan_t scanner);
extern char* javalette_get_text(yyscan_t scanner);

extern yyscan_t javalette__initialize_lexer(FILE * inp);

/* End C preamble code */
%}

%union
{
  int    _int;
  char   _char;
  double _double;
  char*  _string;
  Prog* prog_;
  TopDef* topdef_;
  FnDef* fndef_;
  EVal* eval_;
  ListEVal* listeval_;
  Arg* arg_;
  ListArg* listarg_;
  ListTopDef* listtopdef_;
  BType* btype_;
  OType* otype_;
  AType* atype_;
  Type* type_;
  BracketsOpt* bracketsopt_;
  ListBracketsOpt* listbracketsopt_;
  ListType* listtype_;
  SBlk* sblk_;
  CBlk* cblk_;
  MemItem* memitem_;
  ListMemItem* listmemitem_;
  Memdef* memdef_;
  ListMemdef* listmemdef_;
  CMemdef* cmemdef_;
  ListCMemdef* listcmemdef_;
  Blk* blk_;
  ListStmt* liststmt_;
  Stmt* stmt_;
  Item* item_;
  ListItem* listitem_;
  Expr* expr_;
  DimExpr* dimexpr_;
  ListDimExpr* listdimexpr_;
  ListExpr* listexpr_;
  AddOp* addop_;
  MulOp* mulop_;
  RelOp* relop_;
}

%{
void yyerror(YYLTYPE *loc, yyscan_t scanner, YYSTYPE *result, const char *msg)
{
  fprintf(stderr, "error: %d,%d: %s at %s\n",
    loc->first_line, loc->first_column, msg, javalette_get_text(scanner));
}

int yyparse(yyscan_t scanner, YYSTYPE *result);

extern int yylex(YYSTYPE *lvalp, YYLTYPE *llocp, yyscan_t scanner);
%}

%token          _ERROR_
%token          _BANG        /* ! */
%token          _BANGEQ      /* != */
%token          _PERCENT     /* % */
%token          _DAMP        /* && */
%token          _LPAREN      /* ( */
%token          _RPAREN      /* ) */
%token          _STAR        /* * */
%token          _PLUS        /* + */
%token          _DPLUS       /* ++ */
%token          _COMMA       /* , */
%token          _MINUS       /* - */
%token          _DMINUS      /* -- */
%token          _RARROW      /* -> */
%token          _DOT         /* . */
%token          _SLASH       /* / */
%token          _COLON       /* : */
%token          _SEMI        /* ; */
%token          _LT          /* < */
%token          _LDARROW     /* <= */
%token          _EQ          /* = */
%token          _DEQ         /* == */
%token          _GT          /* > */
%token          _GTEQ        /* >= */
%token          _LBRACK      /* [ */
%token          _EMPTYBRACK  /* [] */
%token          _RBRACK      /* ] */
%token          _KW_boolean  /* boolean */
%token          _KW_class    /* class */
%token          _KW_double   /* double */
%token          _KW_else     /* else */
%token          _KW_enum     /* enum */
%token          _KW_extends  /* extends */
%token          _KW_false    /* false */
%token          _KW_for      /* for */
%token          _KW_if       /* if */
%token          _KW_int      /* int */
%token          _KW_new      /* new */
%token          _KW_null     /* null */
%token          _KW_return   /* return */
%token          _KW_struct   /* struct */
%token          _KW_true     /* true */
%token          _KW_typedef  /* typedef */
%token          _KW_void     /* void */
%token          _KW_while    /* while */
%token          _LBRACE      /* { */
%token          _DBAR        /* || */
%token          _RBRACE      /* } */
%token<_string> _STRING_
%token<_int>    _INTEGER_
%token<_double> _DOUBLE_
%token<_string> _IDENT_

%type <prog_> Prog
%type <topdef_> TopDef
%type <fndef_> FnDef
%type <eval_> EVal
%type <listeval_> ListEVal
%type <arg_> Arg
%type <listarg_> ListArg
%type <listtopdef_> ListTopDef
%type <btype_> BType
%type <otype_> OType
%type <atype_> AType
%type <type_> Type
%type <bracketsopt_> BracketsOpt
%type <listbracketsopt_> ListBracketsOpt
%type <listtype_> ListType
%type <sblk_> SBlk
%type <cblk_> CBlk
%type <memitem_> MemItem
%type <listmemitem_> ListMemItem
%type <memdef_> Memdef
%type <listmemdef_> ListMemdef
%type <cmemdef_> CMemdef
%type <listcmemdef_> ListCMemdef
%type <blk_> Blk
%type <liststmt_> ListStmt
%type <stmt_> Stmt
%type <item_> Item
%type <listitem_> ListItem
%type <expr_> Expr6
%type <dimexpr_> DimExpr
%type <listdimexpr_> ListDimExpr
%type <expr_> Expr5
%type <expr_> Expr4
%type <expr_> Expr3
%type <expr_> Expr2
%type <expr_> Expr
%type <expr_> Expr1
%type <listexpr_> ListExpr
%type <addop_> AddOp
%type <mulop_> MulOp
%type <relop_> RelOp

%start Prog

%%

Prog : ListTopDef { std::reverse($1->begin(),$1->end()) ;$$ = new Program($1); result->prog_ = $$; }
;
TopDef : _KW_struct _IDENT_ SBlk _SEMI { $$ = new Struct($2, $3); }
  | _KW_typedef _KW_struct _IDENT_ _STAR _IDENT_ _SEMI { $$ = new TypeDef($3, $5); }
  | _KW_typedef _KW_struct _IDENT_ SBlk _STAR _IDENT_ _SEMI { $$ = new TypeDefWS($3, $4, $6); }
  | _KW_enum _IDENT_ _LBRACE ListEVal _RBRACE _SEMI { std::reverse($4->begin(),$4->end()) ;$$ = new Enum($2, $4); }
  | _KW_class _IDENT_ CBlk { $$ = new Class($2, $3); }
  | _KW_class _IDENT_ _KW_extends _IDENT_ CBlk { $$ = new ClassWE($2, $4, $5); }
  | FnDef { $$ = new GFuncDef($1); }
;
FnDef : Type _IDENT_ _LPAREN ListArg _RPAREN Blk { std::reverse($4->begin(),$4->end()) ;$$ = new FuncDef($1, $2, $4, $6); }
;
EVal : _IDENT_ { $$ = new EnumValue($1); }
;
ListEVal : /* empty */ { $$ = new ListEVal(); }
  | EVal { $$ = new ListEVal(); $$->push_back($1); }
  | EVal _COMMA ListEVal { $3->push_back($1); $$ = $3; }
;
Arg : Type _IDENT_ { $$ = new Argument($1, $2); }
;
ListArg : /* empty */ { $$ = new ListArg(); }
  | Arg { $$ = new ListArg(); $$->push_back($1); }
  | Arg _COMMA ListArg { $3->push_back($1); $$ = $3; }
;
ListTopDef : TopDef { $$ = new ListTopDef(); $$->push_back($1); }
  | TopDef ListTopDef { $2->push_back($1); $$ = $2; }
;
BType : _KW_int { $$ = new Int(); }
  | _KW_double { $$ = new Doub(); }
  | _KW_boolean { $$ = new Bool(); }
  | _KW_void { $$ = new Void(); }
;
OType : _IDENT_ { $$ = new ObjT($1); }
;
AType : Type BracketsOpt { $$ = new Array($1, $2); }
;
Type : BType { $$ = new BaseType($1); }
  | OType { $$ = new ObjType($1); }
  | AType { $$ = new ArrType($1); }
;
BracketsOpt : _EMPTYBRACK { $$ = new BracketsEmpty(); }
;
ListBracketsOpt : BracketsOpt { $$ = new ListBracketsOpt(); $$->push_back($1); }
  | BracketsOpt ListBracketsOpt { $2->push_back($1); $$ = $2; }
;
ListType : /* empty */ { $$ = new ListType(); }
  | Type { $$ = new ListType(); $$->push_back($1); }
  | Type _COMMA ListType { $3->push_back($1); $$ = $3; }
;
SBlk : _LBRACE ListMemdef _RBRACE { $$ = new SBlock($2); }
;
CBlk : _LBRACE ListCMemdef _RBRACE { $$ = new CBlock($2); }
;
MemItem : _IDENT_ { $$ = new MemberItem($1); }
;
ListMemItem : /* empty */ { $$ = new ListMemItem(); }
  | MemItem { $$ = new ListMemItem(); $$->push_back($1); }
  | MemItem _COMMA ListMemItem { $3->push_back($1); $$ = $3; }
;
Memdef : Type ListMemItem _SEMI { std::reverse($2->begin(),$2->end()) ;$$ = new MemberDef($1, $2); }
;
ListMemdef : /* empty */ { $$ = new ListMemdef(); }
  | ListMemdef Memdef { $1->push_back($2); $$ = $1; }
;
CMemdef : Memdef { $$ = new CVarDef($1); }
  | FnDef { $$ = new CFuncDef($1); }
;
ListCMemdef : /* empty */ { $$ = new ListCMemdef(); }
  | ListCMemdef CMemdef { $1->push_back($2); $$ = $1; }
;
Blk : _LBRACE ListStmt _RBRACE { $$ = new Block($2); }
;
ListStmt : /* empty */ { $$ = new ListStmt(); }
  | ListStmt Stmt { $1->push_back($2); $$ = $1; }
;
Stmt : _SEMI { $$ = new Empty(); }
  | Blk { $$ = new BStmt($1); }
  | Type ListItem _SEMI { std::reverse($2->begin(),$2->end()) ;$$ = new Decl($1, $2); }
  | Expr _SEMI { $$ = new SExp($1); }
  | Expr _EQ Expr _SEMI { $$ = new Ass($1, $3); }
  | _KW_return Expr _SEMI { $$ = new Ret($2); }
  | _KW_return _SEMI { $$ = new VRet(); }
  | _KW_if _LPAREN Expr _RPAREN Stmt { $$ = new Cond($3, $5); }
  | _KW_if _LPAREN Expr _RPAREN Stmt _KW_else Stmt { $$ = new CondElse($3, $5, $7); }
  | _KW_while _LPAREN Expr _RPAREN Stmt { $$ = new While($3, $5); }
  | _KW_for _LPAREN Type _IDENT_ _COLON Expr _RPAREN Stmt { $$ = new ForLoop($3, $4, $6, $8); }
;
Item : _IDENT_ { $$ = new NoInit($1); }
  | _IDENT_ _EQ Expr { $$ = new Init($1, $3); }
;
ListItem : Item { $$ = new ListItem(); $$->push_back($1); }
  | Item _COMMA ListItem { $3->push_back($1); $$ = $3; }
;
Expr6 : _LPAREN Type _RPAREN Expr6 { $$ = new Ecast($2, $4); }
  | _KW_null { $$ = new ELitNull(); }
  | _INTEGER_ { $$ = new ELitInt($1); }
  | _DOUBLE_ { $$ = new ELitDoub($1); }
  | _KW_true { $$ = new ELitTrue(); }
  | _KW_false { $$ = new ELitFalse(); }
  | _STRING_ { $$ = new EString($1); }
  | _IDENT_ { $$ = new EVar($1); }
  | _IDENT_ _LPAREN ListExpr _RPAREN { std::reverse($3->begin(),$3->end()) ;$$ = new EApp($1, $3); }
  | _KW_new OType { $$ = new ENewObj($2); }
  | Expr6 _RARROW _IDENT_ { $$ = new EArrow($1, $3); }
  | Expr6 _DOT _IDENT_ { $$ = new Epropety($1, $3); }
  | Expr6 _DOT _IDENT_ _LPAREN ListExpr _RPAREN { std::reverse($5->begin(),$5->end()) ;$$ = new EFunc($1, $3, $5); }
  | _KW_new BType ListDimExpr { std::reverse($3->begin(),$3->end()) ;$$ = new ENewBArr($2, $3); }
  | _KW_new OType ListDimExpr { std::reverse($3->begin(),$3->end()) ;$$ = new ENewOArr($2, $3); }
  | Expr6 ListDimExpr { std::reverse($2->begin(),$2->end()) ;$$ = new EAcc($1, $2); }
  | Expr6 _DPLUS { $$ = new EInc($1); }
  | Expr6 _DMINUS { $$ = new EDecr($1); }
  | _LPAREN Expr _RPAREN { $$ = $2; }
;
DimExpr : _LBRACK Expr _RBRACK { $$ = new Dim($2); }
;
ListDimExpr : DimExpr { $$ = new ListDimExpr(); $$->push_back($1); }
  | DimExpr ListDimExpr { $2->push_back($1); $$ = $2; }
;
Expr5 : _MINUS Expr6 { $$ = new ENeg($2); }
  | _BANG Expr5 { $$ = new ENot($2); }
  | Expr6 { $$ = $1; }
;
Expr4 : Expr4 MulOp Expr5 { $$ = new EMul($1, $2, $3); }
  | Expr5 { $$ = $1; }
;
Expr3 : Expr3 AddOp Expr4 { $$ = new EAdd($1, $2, $3); }
  | Expr2 _DAMP Expr1 { $$ = new EAnd($1, $3); }
  | Expr4 { $$ = $1; }
;
Expr2 : Expr2 RelOp Expr3 { $$ = new ERel($1, $2, $3); }
  | Expr3 { $$ = $1; }
;
Expr : Expr1 _DBAR Expr { $$ = new EOr($1, $3); }
  | Expr1 { $$ = $1; }
;
Expr1 : Expr2 { $$ = $1; }
;
ListExpr : /* empty */ { $$ = new ListExpr(); }
  | Expr { $$ = new ListExpr(); $$->push_back($1); }
  | Expr _COMMA ListExpr { $3->push_back($1); $$ = $3; }
;
AddOp : _PLUS { $$ = new Plus(); }
  | _MINUS { $$ = new Minus(); }
;
MulOp : _STAR { $$ = new Times(); }
  | _SLASH { $$ = new Div(); }
  | _PERCENT { $$ = new Mod(); }
;
RelOp : _LT { $$ = new LTH(); }
  | _LDARROW { $$ = new LE(); }
  | _GT { $$ = new GTH(); }
  | _GTEQ { $$ = new GE(); }
  | _DEQ { $$ = new EQU(); }
  | _BANGEQ { $$ = new NE(); }
;

%%


/* Entrypoint: parse Prog* from file. */
Prog* pProg(FILE *inp)
{
  YYSTYPE result;
  yyscan_t scanner = javalette__initialize_lexer(inp);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  int error = yyparse(scanner, &result);
  javalette_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.prog_;
  }
}

/* Entrypoint: parse Prog* from string. */
Prog* psProg(const char *str)
{
  YYSTYPE result;
  yyscan_t scanner = javalette__initialize_lexer(0);
  if (!scanner) {
    fprintf(stderr, "Failed to initialize lexer.\n");
    return 0;
  }
  YY_BUFFER_STATE buf = javalette__scan_string(str, scanner);
  int error = yyparse(scanner, &result);
  javalette__delete_buffer(buf, scanner);
  javalette_lex_destroy(scanner);
  if (error)
  { /* Failure */
    return 0;
  }
  else
  { /* Success */
    return result.prog_;
  }
}



