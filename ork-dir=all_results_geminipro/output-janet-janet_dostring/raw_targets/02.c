#include <janet.h>
#include <stdint.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  /* init Janet */
  janet_init();

  /* fuzz the parser */
  JanetTable *env = janet_core_env();
  JanetBuffer buf = janet_string(data, size);
  Janet result;
  janet_dostring(env, buf.data, buf.data + buf.count, &result);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}