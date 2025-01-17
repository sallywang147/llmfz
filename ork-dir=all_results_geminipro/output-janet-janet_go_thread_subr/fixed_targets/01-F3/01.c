#include <janet.h>
#include <stdint.h>
#include <string.h>

extern "C" {
#include <janet/vm.h>
#include <janet/go.h>
}

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  /* init Janet */
  janet_init();

  /* fuzz the parser */
  JanetEVGenericMessage args;
  JanetEVGenericMessage ret;
  args.data = (uint8_t *)data;
  args.size = size;
  janet_go_thread_subr(&args, &ret);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}