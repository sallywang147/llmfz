#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "SpinelNCPTaskScan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize SpinelNCPTaskScan object
  nl::wpantund::SpinelNCPTaskScan taskScan;

  // Extract integral values for event
  int event = stream.ConsumeIntegral<int>();

  // Extract an array of bytes as a vector. We will use this as our va_list
  std::vector<uint8_t> bytes = stream.ConsumeRemainingBytes<uint8_t>();

  // Cast the byte vector to a va_list
  __va_list_tag* args = reinterpret_cast<__va_list_tag*>(bytes.data());

  // Call the function
  nl::wpantund::SpinelNCPTaskScan::vprocess_event(&taskScan, event, args);

  return 0;
}