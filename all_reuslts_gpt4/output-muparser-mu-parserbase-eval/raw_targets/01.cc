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

  FuzzedDataProvider fuzzed_data(data, size);

  std::string line_string = fuzzed_data.ConsumeRandomLengthString();
  int array_size = fuzzed_data.ConsumeIntegralInRange<int>(1, 100);
  double array[array_size];

  try {
    mu::Parser parser;
    parser.SetExpr(line_string);
    parser.Eval(array, array_size);
  } catch (mu::Parser::exception_type &e) {
  } catch (mu::ParserError &e) {
  }
  return 0;
}