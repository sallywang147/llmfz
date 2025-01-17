#include <janet.h>
#include <stdint.h>
#include <string.h>
#include <fuzzer/FuzzedDataProvider.h>

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  /* init Janet */
  janet_init();

  /* fuzz the function */
  FuzzedDataProvider stream(data, size);

  // Create and initialize the JanetEVGenericMessage structs
  JanetEVGenericMessage args;
  JanetEVGenericMessage result;

  // Consume data for the arguments
  args.argc = stream.ConsumeIntegral<int32_t>();
  args.argv = (Janet *)stream.ConsumeBytes<uint8_t>(args.argc * sizeof(Janet)).data();
  args.fiber = NULL;
  args.is_done = stream.ConsumeBool();

  // Call the function to fuzz
  janet_go_thread_subr(&args, &result);

  /* cleanup Janet */
  janet_deinit();

  return 0;
}