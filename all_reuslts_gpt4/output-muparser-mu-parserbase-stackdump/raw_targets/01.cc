#include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <stack>
#include <string>

#include "muParser.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;  // Not enough data to proceed.
  }
  
  FuzzedDataProvider provider(data, size);

  // Create two stacks from the provided data.
  std::stack<double> stack1;
  std::stack<double> stack2;
  
  while (provider.remaining_bytes() > 0) {
    double value = provider.ConsumeFloatingPoint<double>();
    // Distribute values between two stacks.
    if (provider.ConsumeBool()) {
      stack1.push(value);
    } else {
      stack2.push(value);
    }
  }

  try {
    mu::Parser parser;
    parser.StackDump(&stack1, &stack2);
  } catch (mu::Parser::exception_type &e) {
  } catch (mu::ParserError &e) {
  }
  return 0;
}