#include <janet.h>
#include <stdint.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  /* init Janet */
  janet_init();

  /* fuzz the parser */
  JanetTable *env = janet_core_env(NULL);
  Janet result;
  FuzzedDataProvider stream(data, size);

  std::string str1 = stream.ConsumeRandomLengthString();
  std::string str2 = stream.ConsumeRemainingBytesAsString();

  janet_dostring(env, const_cast<char*>(str1.c_str()), const_cast<char*>(str2.c_str()), &result);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}