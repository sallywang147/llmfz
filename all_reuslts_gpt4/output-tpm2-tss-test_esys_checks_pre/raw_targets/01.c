#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tss2-esys/esys_iutil.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct TSS2_TEST_ESYS_CONTEXT test_ctx;
  test_ctx.size = stream.ConsumeIntegral<size_t>();
  test_ctx.data = stream.ConsumeRemainingBytes<uint8_t>().data();

  int result = test_esys_checks_pre(&test_ctx);

  return 0;
}