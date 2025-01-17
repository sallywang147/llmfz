#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "spinel-ncp-task-joiner-commissioning.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Create an instance of the SpinelNCPTaskJoinerCommissioning class
  nl::wpantund::SpinelNCPTaskJoinerCommissioning spinelNCPTaskJoinerCommissioning;

  // Extract an integer for the event parameter
  int event = stream.ConsumeIntegral<int>();

  // Create a va_list and initialize it with the remaining data
  __va_list_tag args;
  args.gp_offset = 0;
  args.fp_offset = 0;
  args.overflow_arg_area = (void *)stream.ConsumeRemainingBytes().data();
  args.reg_save_area = nullptr;

  // Call the function with the fuzzed parameters
  int ret = spinelNCPTaskJoinerCommissioning.vprocess_event(&spinelNCPTaskJoinerCommissioning, event, &args);

  return 0;
}