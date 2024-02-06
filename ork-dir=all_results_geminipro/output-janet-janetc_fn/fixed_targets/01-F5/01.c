#include <janet.h>
#include <stdint.h>
#include <string.h>

extern "C" {
#include <janetc.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  /* init Janet */
  janet_init();

  /* fuzz the function */
  JanetSlot opts;
  janet_slot_init_empty(&opts);

  JanetFopts fopts;
  janet_fopts_init(&fopts, &opts);

  /* Convert the data to a JanetBuffer. */
  JanetBuffer buffer = janet_buffer(data, size);

  union Janet v;
  janetc_fn(&opts, &fopts, &buffer, &v);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}