#include <fuzzer/FuzzedDataProvider.h>
#include <nl/wpantund/spinel.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int event = stream.ConsumeIntegral<int>();
  const std::vector<uint8_t> args = stream.ConsumeRemainingBytes();
  nl::wpantund::SpinelNCPTaskScan task;
  task.vprocess_event(&task, event,
                      reinterpret_cast<struct __va_list_tag*>(args.data()));
  return 0;
}