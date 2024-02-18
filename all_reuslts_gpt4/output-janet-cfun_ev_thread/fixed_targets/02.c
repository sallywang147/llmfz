#include <janet.h>
#include <stdint.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  /* init Janet */
  janet_init();

  /* fuzz the function */
  FuzzedDataProvider stream(data, size);
  int arg1 = stream.ConsumeIntegral<int>();
  Janet arg2;
  arg2.number = stream.ConsumeFloatingPoint<double>();
  cfun_ev_thread(arg1, &arg2);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}