#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <map>

extern "C" {
#include "muParser.h"
#include <cstring>
#include <stdexcept>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string line_string((char *)data, size);
  try {
    mu::Parser parser;
    parser.SetExpr(line_string);
    parser.Eval();
    std::map<std::string, mu::value_type> *used_var = parser.GetUsedVar();
  } catch (mu::Parser::exception_type &e) {
  } catch (mu::ParserError &e) {
  }
  return 0;
}