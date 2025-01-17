#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "tao/pegtl.hpp"
#include "usbguard/Rule.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume the data to create a string
  std::string str = stream.ConsumeRemainingBytesAsString();
  tao::pegtl::string_input<> in(str, "fuzz_input");

  // Create a Rule object
  usbguard::Rule rule;

  // Create a tracer
  tao::pegtl::tracer tr;

  // Call the function
  decltype(in, &rule, &tr);

  return 0;
}