#include <janet.h>
#include <stdint.h>
#include <string.h>

extern "C" {
#include "janet.c" // Include the Janet C source file
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  /* init Janet */
  janet_init();

  /* fuzz the parser */
  JanetTable *env = janet_table();
  JanetTable *globals = janet_table();
  Janet *ret = janet_dobytes(env, (char *)data, size, (char *)data, globals);
  janet_decref(ret);
  janet_table_dec(env);
  janet_table_dec(globals);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}