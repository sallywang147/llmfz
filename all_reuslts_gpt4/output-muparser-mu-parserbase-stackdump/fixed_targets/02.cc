#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <stack>

#include "muParser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string line_string((char *)data, size);
  try {
    mu::Parser parser;
    parser.SetExpr(line_string);
    parser.Eval();

    std::stack<double> valStack;
    std::stack<int> oprtStack;

    parser.StackDump(&valStack, &oprtStack);
  } catch (mu::Parser::exception_type &e) {
  } catch (mu::ParserError &e) {
  }
  return 0;
}