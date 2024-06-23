#include <cstdio>
#include <string>
#include <iostream>
#include "Parser.H"
#include "Printer.H"
#include "Absyn.H"
#include "ParserError.H"

void usage() {
  printf("usage: Call with one of the following argument combinations:\n");
  printf("\t--help\t\tDisplay this help message.\n");
  printf("\t(no arguments)\tParse stdin verbosely.\n");
  printf("\t(files)\t\tParse content of files verbosely.\n");
  printf("\t-s (files)\tSilent mode. Parse content of files silently.\n");
}

std::string output_dir = "build/test/";

int main(int argc, char ** argv)
{
  FILE *input;
  int quiet = 0;
  char *filename = NULL;

  if (argc > 1) {
    if (strcmp(argv[1], "-s") == 0) {
      quiet = 1;
      if (argc > 2) {
        filename = argv[2];
      } else {
        input = stdin;
      }
    } else {
      filename = argv[1];
    }
  }

  if (filename) {
    input = fopen(filename, "r");
    if (!input) {
      usage();
      exit(1);
    }
  } else input = stdin;

  // new file name for the output
  if (filename == NULL) {
    filename = (char *) "stdin";
  }
  // get the name of the file to write the AST to
  std::string file_base_name = std::string(filename);
  std::cout << file_base_name << std::endl;
  size_t lastindex = file_base_name.find_last_of("/");
  if (lastindex != std::string::npos) {
    file_base_name = file_base_name.substr(lastindex, file_base_name.size());
  }
  std::string ast_file_name = output_dir + file_base_name + ".ast";


  /* The default entry point is used. For other options see Parser.H */
  Prog *parse_tree = NULL;
  try {
  parse_tree = pProg(input);
  } catch( parse_error &e) {
     std::cerr << "Parse error on line " << e.getLine() << "\n";
  }
  if (parse_tree)
  { 
    PrintAbsyn *p = new PrintAbsyn();
    ShowAbsyn *s = new ShowAbsyn();
    if (!quiet) {
        printf("\nParse Successful!\n");
        printf("\n[Abstract Syntax]\n");
        
        printf("%s\n\n", s->show(parse_tree));
        printf("[Linearized Tree]\n");
        printf("%s\n\n", p->print(parse_tree));
    }
    // write the AST to a file
    FILE *ast_file = fopen(ast_file_name.c_str(), "w");
    if (ast_file == NULL) {
      std::cerr << "Error: Could not open file " << ast_file_name << std::endl;
      return 1;
    }
    fprintf(ast_file, "%s\n", s->show(parse_tree));

    delete(parse_tree);
    std::cerr << "OK" << std::endl;
    return 0;
  }
  std::cerr << "ERROR" << std::endl;
  return 1;
}

