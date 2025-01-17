#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <tao/pegtl.hpp>
#include <usbguard/RuleParser.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string input_string = stream.ConsumeRemainingBytesAsString();
  tao::pegtl::string_input<> in(input_string, "fuzz_input");
  usbguard::Rule rule;

  tao::pegtl::tracer tracer;
  tao::pegtl::internal::seq<usbguard::RuleParser::condition, tao::pegtl::internal::star<tao::pegtl::plus<tao::pegtl::ascii::blank>, usbguard::RuleParser::condition> >::match(&in, &rule, &tracer);

  return 0;
}