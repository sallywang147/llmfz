#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <stdarg.h>

#include "SpinelNCPInstance.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize SpinelNCPInstance
  nl::wpantund::SpinelNCPInstance spinelInstance;

  // Consume data for the integer parameter
  int int_arg = stream.ConsumeIntegral<int>();

  // Create a va_list
  va_list args;
  va_start(args, int_arg);

  // Create a __va_list_tag from the va_list
  __va_list_tag* va_list_tag = reinterpret_cast<__va_list_tag*>(args);

  // Call the function
  spinelInstance.vprocess_event(&spinelInstance, int_arg, va_list_tag);

  va_end(args);

  return 0;
}