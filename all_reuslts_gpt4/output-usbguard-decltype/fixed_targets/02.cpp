#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tao/pegtl.hpp"
#include "usbguard/Rule.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a string from the input data to be used with string_input
  std::string input_string = stream.ConsumeRemainingBytesAsString();
  tao::pegtl::string_input<> in(input_string, "");

  // Create a Rule object
  usbguard::Rule rule;

  // Create a tracer
  tao::pegtl::tracer tr;

  // Call the target function
  bool result = decltype(&in, &rule, &tr);

  return 0;
}