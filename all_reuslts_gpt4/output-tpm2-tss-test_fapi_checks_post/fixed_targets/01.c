#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>

#include "tss2_test_fapi_context.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a TSS2_TEST_FAPI_CONTEXT object
  struct TSS2_TEST_FAPI_CONTEXT test_ctx;

  // Initialize the structure fields using the FuzzedDataProvider
  test_ctx.field1 = stream.ConsumeIntegral<int>();
  test_ctx.field2 = stream.ConsumeIntegral<int>();
  test_ctx.field3 = stream.ConsumeIntegral<int>();
  test_ctx.field4 = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  return test_fapi_checks_post(&test_ctx);
}