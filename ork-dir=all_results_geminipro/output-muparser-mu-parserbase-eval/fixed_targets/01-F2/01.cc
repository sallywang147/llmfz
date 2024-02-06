#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string>

using namespace mu;

extern "C" {
#include "muParser.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string line_string((char *)data, size);
  try {
    Parser parser;
    parser.SetExpr(line_string);
    double d;
    parser.Eval(&d);
  } catch (Parser::exception_type &e) {
  } catch (ParserError &e) {
  }
  return 0;
}