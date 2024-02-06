#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tss2_test_fapi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a TSS2_TEST_FAPI_CONTEXT object
  struct TSS2_TEST_FAPI_CONTEXT test_ctx;

  // Consume data from the stream to initialize the TSS2_TEST_FAPI_CONTEXT object
  test_ctx.magic = stream.ConsumeIntegral<uint32_t>();
  test_ctx.version = stream.ConsumeIntegral<uint32_t>();
  test_ctx.tcti = stream.ConsumeIntegral<uint32_t>();
  test_ctx.sys = stream.ConsumeIntegral<uint32_t>();
  test_ctx.sapi_context = stream.ConsumeIntegral<uint32_t>();
  test_ctx.esys_context = stream.ConsumeIntegral<uint32_t>();
  test_ctx.fapi_context = stream.ConsumeIntegral<uint32_t>();
  test_ctx.command = stream.ConsumeIntegral<uint32_t>();
  test_ctx.response = stream.ConsumeIntegral<uint32_t>();
  test_ctx.response_size = stream.ConsumeIntegral<size_t>();
  test_ctx.flags = stream.ConsumeIntegral<uint32_t>();

  // Call the function to be fuzzed
  int result = test_fapi_checks_post(&test_ctx);

  // The return value is ignored because we're only interested in the function's
  // behavior, not its output.
  (void)result;

  return 0;
}