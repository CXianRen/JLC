#include <cstdio>
#include <string>
#include <iostream>
#include "Parser.H"
#include "Printer.H"
#include "Absyn.H"
#include "ParserError.H"

#include "common/jlc_context.h"
#include "typechecker/jlc_tc_error.h"
#include "typechecker/jlc_tc_udt_dcl.h"
#include "typechecker/jlc_tc_func_dcl.h"
#include "typechecker/jlc_tc_udt_def.h"
#include "typechecker/jlc_tc_func_def.h"

void usage()
{
  printf("usage: Call with one of the following argument combinations:\n");
  printf("\t--help\t\tDisplay this help message.\n");
  printf("\t(no arguments)\tParse stdin verbosely.\n");
  printf("\t(files)\t\tParse content of files verbosely.\n");
  printf("\t-s (files)\tSilent mode. Parse content of files silently.\n");
}

int main(int argc, char **argv)
{
  FILE *input;
  int quiet = 0;
  char *filename = NULL;

  if (argc > 1)
  {
    if (strcmp(argv[1], "-s") == 0)
    {
      quiet = 1;
      if (argc > 2)
      {
        filename = argv[2];
      }
      else
      {
        input = stdin;
      }
    }
    else
    {
      filename = argv[1];
    }
  }

  if (filename)
  {
    input = fopen(filename, "r");
    if (!input)
    {
      usage();
      exit(1);
    }
  }
  else
    input = stdin;
  /* The default entry point is used. For other options see Parser.H */
  Prog *parse_tree = NULL;
  try
  {
    parse_tree = pProg(input);
  }
  catch (parse_error &e)
  {
    std::cerr << "Parse error on line " << e.getLine() << "\n";
  }
  if (parse_tree)
  {
    if (!quiet)
    {
      printf("\nParse Successful!\n");
      printf("\n[Abstract Syntax]\n");
      ShowAbsyn *s = new ShowAbsyn();
      printf("%s\n\n", s->show(parse_tree));
      printf("[Linearized Tree]\n");
      PrintAbsyn *p = new PrintAbsyn();
      printf("%s\n\n", p->print(parse_tree));
    }

    // new context
    auto context =
        std::make_shared<JLC::CONTEXT::JLCContext>();

    // new jlc tc udt dcl
    auto udt_dc_checker =
        std::make_shared<JLC::TC::JLC_UDT_DC_Checker>(context);

    // new jlc tc func dcl
    auto func_dc_checker =
        std::make_shared<JLC::TC::JLC_FUNC_CD_Checker>(context);

    // new jlc tc udt def
    auto udt_def_checker =
        std::make_shared<JLC::TC::JLC_TC_UDT_DEF_Checker>(context);
      
    // new jlc tc func def
    auto func_def_checker =
        std::make_shared<JLC::TC::JLC_FUNC_DEF_Checker>(context);

    try
    {
      parse_tree->accept(udt_dc_checker.get());
      parse_tree->accept(func_dc_checker.get());
      parse_tree->accept(udt_def_checker.get());
      parse_tree->accept(func_def_checker.get());
    }
    catch (JLC::TC::JLCTCError &e)
    {
      std::cerr << "ERROR, Type check error:\n " << e.what() << "\n";
      return 1;
    }

    delete (parse_tree);
    std::cerr << "OK" << std::endl;
    return 0;
  }
  std::cerr << "ERROR" << std::endl;
  return 1;
}
