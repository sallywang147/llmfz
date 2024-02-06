#include <cstdint>
#include <fuzzer/FuzzedDataProvider.h>
#include "exprtk.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int int_arg = stream.ConsumeIntegral<int>();
  bool bool_arg = stream.ConsumeBool();

  // Initialize expression_generator
  exprtk::parser<float>::expression_generator<float> generator;

  // Call the target function
  exprtk::details::expression_node *node = generator(&generator, &int_arg, bool_arg);

  // Free the memory allocated for the node
  if (node != nullptr) {
    delete node;
  }

  return 0;
}