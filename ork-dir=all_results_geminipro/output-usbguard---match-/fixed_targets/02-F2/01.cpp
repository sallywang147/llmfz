#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <string>

#include "usbguard/RuleParser.hpp"
#include "tao/pegtl.hpp"
#include "tao/pegtl/contrib/tracer.hpp"

namespace tao::pegtl {
namespace internal {
template <>
struct action<usbguard::RuleParser::condition> {
  template <typename Input>
  static bool apply(const Input& in, usbguard::Rule *r, Tracer& t) {
    (void)in;
    (void)r;
    (void)t;
    return true;
  }
};
}
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::string input = provider.ConsumeRemainingBytesAsString();

  usbguard::RuleParser::condition condition;
  usbguard::Rule rule;
  tao::pegtl::tracer tracer;

  bool result = tao::pegtl::internal::seq<
      usbguard::RuleParser::condition,
      tao::pegtl::internal::star<tao::pegtl::plus<tao::pegtl::ascii::blank>,
                                 usbguard::RuleParser::condition>
  >::match(input.data(), &rule, tracer);

  (void)result;
  (void)condition;
  return 0;
}