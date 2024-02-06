#include <fuzzer/FuzzedDataProvider.h>
#include <usbguard/RuleParser.hpp>
#include <tao/pegtl.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string input_string = stream.ConsumeRemainingBytesAsString();
  usbguard::Rule rule;
  tao::pegtl::string_input<> in(input_string, "fuzz_input");
  tao::pegtl::tracer tr(in);

  tao::pegtl::internal::seq<
    usbguard::RuleParser::condition,
    tao::pegtl::internal::star<
      tao::pegtl::plus<tao::pegtl::ascii::blank>,
      usbguard::RuleParser::condition
    >
  >::match(&in, &rule, &tr);

  return 0;
}