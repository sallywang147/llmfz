#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "tss2/tss2_test_fapi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a TSS2_TEST_FAPI_CONTEXT object
  struct TSS2_TEST_FAPI_CONTEXT test_ctx;

  // Consume data from the fuzzer input
  size_t consumed = stream.ConsumeData(&test_ctx, sizeof(test_ctx));

  // If we could not consume enough data for the struct, return early.
  if (consumed != sizeof(test_ctx)) {
    return 0;
  }

  // Call the function to be fuzzed
  test_fapi_checks_pre(&test_ctx);

  return 0;
}