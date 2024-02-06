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
    mu::Parser parser;  // Fix: Declare parser correctly
    parser.SetExpr(line_string);
    parser.Eval();  // Fix: Call parser.Eval()
    std::stack<mu::value> value_stack;
    std::stack<mu::token> token_stack;
    parser.StackDump(&value_stack, &token_stack);  // Fix: Use correct arguments
  } catch (mu::Parser::exception_type &e) {
    std::cerr << "Parser exception: " << e.GetMsg() << std::endl;  // Fix: Use std::cerr
  } catch (mu::ParserError &e) {
    std::cerr << "Parser error: " << e.GetMsg() << std::endl;  // Fix: Use std::cerr
  }
  return 0;
}