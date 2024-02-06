#include <cstdint>
#include <string>
#include "exprtk.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  int int_arg = stream.ConsumeIntegral<int>();
  bool bool_arg = stream.ConsumeBool();

  exprtk::parser<float>::expression_generator<float> generator;
  exprtk::details::expression_node *node = generator(&generator, &int_arg, bool_arg);

  return 0;
}