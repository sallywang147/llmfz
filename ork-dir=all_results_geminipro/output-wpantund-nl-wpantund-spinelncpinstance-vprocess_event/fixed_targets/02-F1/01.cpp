#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

namespace nl {
namespace wpantund {
class SpinelNCPInstance {
 public:
  int vprocess_event(int, va_list);
};
}  // namespace wpantund
}  // namespace nl

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  nl::wpantund::SpinelNCPInstance instance;
  const int event_id = stream.ConsumeIntegral<int>();
  const std::vector<uint8_t> payload =
      stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange<size_t>(0, 1024));
  instance.vprocess_event(event_id, reinterpret_cast<va_list>(payload.data()));
  return 0;
}