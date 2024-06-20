/* A Bison parser, made by GNU Bison 3.7.5.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_JAVALETTE_BISON_H_INCLUDED
# define YY_JAVALETTE_BISON_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int javalette_debug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    _ERROR_ = 258,                 /* _ERROR_  */
    _LPAREN = 259,                 /* _LPAREN  */
    _RPAREN = 260,                 /* _RPAREN  */
    _STAR = 261,                   /* _STAR  */
    _COMMA = 262,                  /* _COMMA  */
    _SEMI = 263,                   /* _SEMI  */
    _EMPTYBRACK = 264,             /* _EMPTYBRACK  */
    _KW_boolean = 265,             /* _KW_boolean  */
    _KW_class = 266,               /* _KW_class  */
    _KW_double = 267,              /* _KW_double  */
    _KW_enum = 268,                /* _KW_enum  */
    _KW_extends = 269,             /* _KW_extends  */
    _KW_int = 270,                 /* _KW_int  */
    _KW_struct = 271,              /* _KW_struct  */
    _KW_typedef = 272,             /* _KW_typedef  */
    _KW_void = 273,                /* _KW_void  */
    _LBRACE = 274,                 /* _LBRACE  */
    _RBRACE = 275,                 /* _RBRACE  */
    _IDENT_ = 276                  /* _IDENT_  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 50 "Javalette.y"

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
  Type* type_;
  BracketsOpt* bracketsopt_;
  ListBracketsOpt* listbracketsopt_;
  ListType* listtype_;
  SBlk* sblk_;
  CBlk* cblk_;
  Memdef* memdef_;
  ListMemdef* listmemdef_;
  CMemdef* cmemdef_;
  ListCMemdef* listcmemdef_;
  Blk* blk_;
  ListStmt* liststmt_;
  Stmt* stmt_;

#line 113 "Bison.H"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int javalette_parse (yyscan_t scanner, YYSTYPE *result);

#endif /* !YY_JAVALETTE_BISON_H_INCLUDED  */
