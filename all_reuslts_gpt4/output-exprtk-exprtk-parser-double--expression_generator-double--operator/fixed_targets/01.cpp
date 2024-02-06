#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>

#include "exprtk.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  exprtk::parser<double>::expression_generator<double> generator;
  int int_arg = stream.ConsumeIntegral<int>();
  bool bool_arg = stream.ConsumeBool();

  generator(&generator, &int_arg, bool_arg);

  return 0;
}