#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "tss2-esys/esys_iutil.h"
#include "tss2-esys/esys_mu.h"
#include "tss2-esys/esys_int.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize the test context
  struct TSS2_TEST_ESYS_CONTEXT test_ctx;
  
  // Fill the test context with data from the fuzzer
  size_t consumed = stream.ConsumeData(&test_ctx, sizeof(test_ctx));
  if (consumed != sizeof(test_ctx)) {
    // Not enough data to fill the test context
    return 0;
  }
  
  // Call the function to be fuzzed
  int result = test_esys_checks_post(&test_ctx);
  
  return 0;
}