#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <string>

#include "tao/pegtl.hpp"
#include "usbguard/Rule.hpp"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string input = stream.ConsumeRemainingBytesAsString();

  tao::pegtl::string_input in(input, "");
  usbguard::Rule rule;
  tao::pegtl::tracer tracer(in);

  bool result = decltype(rule)(&in, &rule, &tracer);
  (void)result;

  return 0;
}