#include <janet.h>
#include <stdint.h>

extern "C" {
#include <janetc.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  /* init Janet */
  janet_init();

  /* fuzz the function */
  JanetSlot opts[1];
  janet_slot_init(opts, JANET_NIL);
  JanetFopts fopts;
  janet_fopts_init(&fopts);
  union Janet *args[1];
  args[0] = janet_wrap_string(data);

  janetc_fn(opts, &fopts, 1, args);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}