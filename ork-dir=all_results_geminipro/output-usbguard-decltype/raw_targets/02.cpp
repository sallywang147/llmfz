#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>
#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/tracer.hpp>
#include <usbguard/Rule.hpp>

using namespace tao::pegtl;
using namespace usbguard;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string input = stream.ConsumeRemainingBytesAsString();
  string_input in(input.data(), input.data() + input.size());

  Rule rule;
  rule.parse(in);

  tracer trace;
  decltype(in, &rule, &trace);

  return 0;
}