#include <janet.h>
#include <stdint.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  /* init Janet */
  janet_init();
  
  /* create environment */
  JanetTable *env = janet_core_env(NULL);

  /* create buffer for script */
  std::string script = stream.ConsumeRemainingBytesAsString();
  char *script_cstr = const_cast<char*>(script.c_str());

  /* create buffer for name */
  char name[] = "fuzz";

  /* create a Janet object */
  union Janet out;

  /* call the function to fuzz */
  janet_dostring(env, script_cstr, name, &out);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}