#include <janet.h>
#include <stdint.h>
#include <string.h>

extern "C" {
#include <sanitizer/libfuzzer/libfuzzer_macro.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  /* init Janet */
  janet_init();

  /* fuzz the parser */
  struct JanetEVGenericMessage args;
  args.type = JANET_EV_GENERIC_MESSAGE_TYPE_MESSAGE;
  args.message.data = (uint8_t *)data;
  args.message.length = size;
  struct JanetEVGenericMessage ret;
  janet_go_thread_subr(&args, &ret);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}