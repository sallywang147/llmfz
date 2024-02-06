#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "muParser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string line_string((char *)data, size);
  try {
    mu::Parser parser;
    parser.SetExpr(line_string);
    parser.Eval();
    std::vector<mu::ParserToken> tokens;
    parser.GetUsedVar(tokens);
    for (size_t i = 0; i < tokens.size(); ++i) {
      parser.ApplyStrFunc(&tokens[i], &parser, &tokens[i], &tokens);
    }
  } catch (mu::Parser::exception_type &e) {
  } catch (mu::ParserError &e) {
  }
  return 0;
}