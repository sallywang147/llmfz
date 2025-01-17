#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstdarg>

#include "wpantund/SpinelNCPTaskJoinerCommissioning.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int event = stream.ConsumeIntegral<int>();

  // Initialize a SpinelNCPTaskJoinerCommissioning object
  nl::wpantund::SpinelNCPTaskJoinerCommissioning commissioningTask;

  // Initialize a va_list
  va_list args;
  va_start(args, event);

  // Call the function to fuzz
  commissioningTask.vprocess_event(&commissioningTask, event, reinterpret_cast<struct __va_list_tag *>(args));

  va_end(args);

  return 0;
}