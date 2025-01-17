#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <string>

#include "muParser.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  std::string expr = stream.ConsumeRandomLengthString();
  int numResults = stream.ConsumeIntegralInRange<int>(0, 10);

  std::vector<double> results(numResults);

  try {
    mu::Parser parser;
    parser.SetExpr(expr);
    parser.Eval(&results[0], numResults);
  } catch (mu::Parser::exception_type &e) {
  } catch (mu::ParserError &e) {
  }
  return 0;
}