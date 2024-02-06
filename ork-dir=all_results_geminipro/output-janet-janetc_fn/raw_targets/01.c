#include <janet.h>
#include <stdint.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  /* init Janet */
  janet_init();

  /* fuzz the function */
  JanetSlot opts;
  janet_slot_init_empty(&opts);

  JanetFopts fopts;
  janet_fopts_init(&fopts, &opts);

  union Janet v;
  janetc_fn(&opts, &fopts, 0, &v);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}