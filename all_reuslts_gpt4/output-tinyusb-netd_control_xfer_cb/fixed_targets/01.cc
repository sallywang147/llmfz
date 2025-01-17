#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstring>

#include "tusb.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 2) {
    return 0;
  }

  FuzzedDataProvider fuzzed_data(data, size);

  char rhport = fuzzed_data.ConsumeIntegral<char>();
  char stage = fuzzed_data.ConsumeIntegral<char>();

  struct tusb_control_request_t request;
  if (fuzzed_data.remaining_bytes() < sizeof(request)) {
    return 0;
  }

  fuzzed_data.ConsumeData(&request, sizeof(request));

  netd_control_xfer_cb(rhport, stage, &request);

  return 0;
}