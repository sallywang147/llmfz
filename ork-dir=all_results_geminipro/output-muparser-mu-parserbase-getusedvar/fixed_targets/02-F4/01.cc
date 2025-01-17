#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string>

#include "muParser.h"
#include "muParserException.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string line_string((char *)data, size);
  try {
    mu::Parser parser;
    parser.SetExpr(line_string);
    parser.Eval();
    parser.GetUsedVar();
  } catch (mu::Parser::exception_type &e) {
    std::cerr << "Parser exception: " << e.GetMsg() << std::endl;
  } catch (mu::ParserError &e) {
    std::cerr << "Parser error: " << e.GetMsg() << std::endl;
  }
  return 0;
}