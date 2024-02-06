#include <janet.h>
#include <stdint.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  /* init Janet */
  janet_init();

  /* fuzz the janetc_fn */
  FuzzedDataProvider provider(data, size);

  struct JanetSlot opts;
  struct JanetFopts fopts;
  int n = provider.ConsumeIntegral<int>();
  union Janet *janet_union = nullptr;

  if (provider.remaining_bytes() > 0) {
    size_t union_size = provider.ConsumeIntegralInRange<size_t>(1, provider.remaining_bytes());
    janet_union = reinterpret_cast<union Janet *>(malloc(union_size));
    if (janet_union) {
      memcpy(janet_union, provider.ConsumeRemainingBytes().data(), union_size);
    }
  }

  janetc_fn(&opts, &fopts, n, janet_union);

  if (janet_union) {
    free(janet_union);
  }

  /* cleanup Janet */
  janet_deinit();

  return 0;
}