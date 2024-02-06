#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string>

#include "muParser.h"

extern "C" {
#include "llvm/Support/CommandLine.h"
}

using namespace llvm;

static cl::opt<std::string> InputFile(cl::Positional, cl::desc("<input file>"),
                                      cl::init("-"), cl::value_desc("filename"));

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string line_string((char *)data, size);
  try {
    mu::Parser parser;
    parser.SetExpr(line_string);
    parser.Eval();
    std::stack<mu::Parser::token> op_stack;
    std::stack<mu::Parser::token> val_stack;
    parser.StackDump(&op_stack, &val_stack);
  } catch (mu::Parser::exception_type &e) {
  } catch (mu::ParserError &e) {
  }
  return 0;
}