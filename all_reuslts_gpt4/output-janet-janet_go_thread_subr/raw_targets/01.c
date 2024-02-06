#include <janet.h>
#include <stdint.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  /* init Janet */
  janet_init();

  /* fuzz the function */
  struct JanetEVGenericMessage args;
  struct JanetEVGenericMessage res;

  /* Consume data for args and res */
  size_t consumed = stream.ConsumeData(&args, sizeof(args));
  if (consumed != sizeof(args)) {
    janet_deinit();
    return 0;
  }
  consumed = stream.ConsumeData(&res, sizeof(res));
  if (consumed != sizeof(res)) {
    janet_deinit();
    return 0;
  }

  /* Call the function */
  janet_go_thread_subr(&args, &res);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}