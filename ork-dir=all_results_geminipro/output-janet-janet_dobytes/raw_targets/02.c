#include <janet.h>
#include <stdint.h>
#include <string.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  /* init Janet */
  janet_init();

  /* fuzz the parser */
  JanetTable *env = janet_table();
  JanetBytecode *bc = janet_bytecodes_new(1024);
  janet_bytecodes_write(bc, data, size);
  janet_dobytes(env, (char *)data, size, (char *)bc->data, &bc->val);
  janet_bytecodes_free(bc);
  janet_table_dec(env);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}