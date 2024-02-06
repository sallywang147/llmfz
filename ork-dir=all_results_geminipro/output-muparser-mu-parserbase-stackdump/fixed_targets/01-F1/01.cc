#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string>

extern "C" {
#include "muParser.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string line_string((char *)data, size);
  try {
    mu::Parser parser;
    parser.SetExpr(line_string);
    parser.Eval();
    std::stack<mu::value> value_stack;
    std::stack<mu::token> token_stack;
    parser.StackDump(&value_stack, &token_stack);
  } catch (mu::Parser::exception_type &e) {
  } catch (mu::ParserError &e) {
  }
  return 0;
}