#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "muParser.h"

extern "C" {
#include "llvm/Support/CommandLine.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::string line_string((char *)data, size);
  try {
    mu::Parser parser;
    parser.SetExpr(line_string);
    parser.Eval();
    std::vector<mu::ParserToken> args;
    parser.ApplyStrFunc(nullptr, &parser, nullptr, &args);
  } catch (mu::Parser::exception_type &e) {
  } catch (mu::ParserError &e) {
  }
  return 0;
}