#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#include "SpinelNCPInstance.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < sizeof(int)) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Create a SpinelNCPInstance object
  nl::wpantund::SpinelNCPInstance spinelNCPInstance;

  // Consume an int from the data stream
  int arg = stream.ConsumeIntegral<int>();

  // Create a va_list and pass it to the function
  va_list args;
  va_start(args, arg);

  // Call the function
  spinelNCPInstance.vprocess_event(&spinelNCPInstance, arg, reinterpret_cast<__va_list_tag*>(&args));

  va_end(args);

  return 0;
}