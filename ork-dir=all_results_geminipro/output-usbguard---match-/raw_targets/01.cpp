#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <vector>

#include <fuzzer/FuzzedDataProvider.h>
#include <tao/pegtl.hpp>

namespace tao::pegtl {
  namespace internal {
    template<typename Rule>
    struct action {
      static bool apply(const Rule& /*unused*/, string_input& /*unused*/, tracer& /*unused*/) {
        return true;
      }
    };
  }
}

namespace usbguard {
  struct RuleParser {
    template<typename Input>
    struct condition : tao::pegtl::seq<
      tao::pegtl::plus<tao::pegtl::ascii::blank>,
      tao::pegtl::string<'A'>
    > {};
  };
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> input_buffer(stream.ConsumeRemainingBytes());
  string_input input(input_buffer.data(), input_buffer.size());

  usbguard::RuleParser::Rule rule;
  tao::pegtl::tracer tracer;

  bool result = tao::pegtl::internal::seq<
    usbguard::RuleParser::condition,
    tao::pegtl::internal::star<
      tao::pegtl::plus<tao::pegtl::ascii::blank>,
      usbguard::RuleParser::condition
    >
  >::match<tao::pegtl::internal::action>(input, rule, tracer);
  (void)result;

  return 0;
}