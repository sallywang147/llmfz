#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "wpantund.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  nl::wpantund::SpinelNCPTaskScan* task =
      new nl::wpantund::SpinelNCPTaskScan();
  const int event = stream.ConsumeIntegral<int>();
  const struct __va_list_tag* args = nullptr;
  int result = task->vprocess_event(task, event, args);
  delete task;
  return result;
}