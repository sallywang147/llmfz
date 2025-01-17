#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "SpinelNCPTaskScan.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize SpinelNCPTaskScan object
  nl::wpantund::SpinelNCPTaskScan scan_task;

  // Consume data for event
  int event = stream.ConsumeIntegral<int>();

  // Consume data for args
  __va_list_tag args;
  args.gp_offset = stream.ConsumeIntegral<unsigned int>();
  args.fp_offset = stream.ConsumeIntegral<unsigned int>();
  args.overflow_arg_area = (void *)stream.ConsumeBytes<uint8_t>(stream.remaining_bytes()).data();
  args.reg_save_area = (void *)stream.ConsumeBytes<uint8_t>(stream.remaining_bytes()).data();

  // Call the function to fuzz
  scan_task.vprocess_event(&scan_task, event, &args);

  return 0;
}