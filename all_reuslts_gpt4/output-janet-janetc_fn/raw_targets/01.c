#include <janet.h>
#include <stdint.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  /* init Janet */
  janet_init();

  /* FuzzedDataProvider to generate inputs */
  FuzzedDataProvider provider(data, size);

  /* Create JanetSlot */
  struct JanetSlot opts[1];
  opts[0].flags = provider.ConsumeIntegral<uint32_t>();
  opts[0].value = janet_wrap_number(provider.ConsumeFloatingPoint<double>());

  /* Create JanetFopts */
  struct JanetFopts fopts[1];
  fopts[0].flags = provider.ConsumeIntegral<uint32_t>();
  fopts[0].index = provider.ConsumeIntegral<int32_t>();

  /* Create union.Janet */
  union Janet args[1];
  args[0] = janet_wrap_number(provider.ConsumeFloatingPoint<double>());

  /* Call the function to fuzz */
  janetc_fn(opts, fopts, provider.ConsumeIntegral<int>(), args);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}