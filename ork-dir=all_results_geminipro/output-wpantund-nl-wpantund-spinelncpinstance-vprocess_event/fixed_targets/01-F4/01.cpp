#include <cstdarg>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

namespace nl {
namespace wpantund {

class SpinelNCPInstance {
 public:
  int non_virtual_thunk_to_vprocess_event(int event_id, va_list args) {
    return vprocess_event(event_id, args);
  }

 private:
  int vprocess_event(int event_id, va_list args) { return 0; }
};

}  // namespace wpantund
}  // namespace nl

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int event_id = stream.ConsumeIntegral<int>();
  std::vector<uint8_t> va_list_bytes = stream.ConsumeRemainingBytes();
  va_list va_list_ptr;
  va_copy(va_list_ptr, reinterpret_cast<va_list*>(va_list_bytes.data()));
  nl::wpantund::SpinelNCPInstance* instance_ptr =
      new nl::wpantund::SpinelNCPInstance();
  int ret = instance_ptr->non_virtual_thunk_to_vprocess_event(event_id,
                                                              va_list_ptr);
  va_end(va_list_ptr);
  delete instance_ptr;
  return ret;
}