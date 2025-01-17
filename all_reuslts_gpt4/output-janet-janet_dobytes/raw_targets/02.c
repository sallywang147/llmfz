#include <janet.h>
#include <stdint.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  /* init Janet */
  janet_init();

  /* fuzz the parser */
  FuzzedDataProvider stream(data, size);

  struct JanetTable *env = janet_core_env(NULL);
  char *name = "fuzzer";
  int32_t len = stream.ConsumeIntegral<int32_t>();
  char *src = (char *)stream.ConsumeRemainingBytes().data();
  union Janet *out = NULL;

  janet_dobytes(env, src, len, name, out);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}