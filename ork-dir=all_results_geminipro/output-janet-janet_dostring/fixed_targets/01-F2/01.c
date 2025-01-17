#include <janet.h>
#include <stdint.h>
#include <string.h>

extern "C" {
#include <janet.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  /* init Janet */
  janet_init();

  /* fuzz the parser */
  JanetTable *env = janet_core_env();
  JanetBuffer *buffer = janet_buffer(data, size);
  Janet result;

  janet_dostring(env, buffer, "fuzz", &result);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}