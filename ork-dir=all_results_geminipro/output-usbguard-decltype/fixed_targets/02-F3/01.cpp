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
  if (!rule.parse(in)) {  // Check if there are any errors in the parsing process
    tracer trace(in, &rule, &trace);
    for (const auto& error : trace.errors) {
      std::cerr << error << std::endl;
    }
    return 1;  // Return a non-zero value to indicate that the input is invalid
  }

  return 0;
}