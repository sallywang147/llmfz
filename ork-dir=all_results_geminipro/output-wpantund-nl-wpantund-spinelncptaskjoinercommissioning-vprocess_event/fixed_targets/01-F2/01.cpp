#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" {
#include "nl_wpantund_SpinelNCPTaskJoinerCommissioning.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  nl::wpantund::SpinelNCPTaskJoinerCommissioning* task =
      new nl::wpantund::SpinelNCPTaskJoinerCommissioning();

  const int event = stream.ConsumeIntegral<int>();

  std::vector<uint8_t> args_buffer(1000);
  stream.ConsumeBytes(args_buffer.data(), args_buffer.size());
  va_list args;
  va_copy(args, args_buffer.data());
  task->vprocess_event(task, event, &args);
  delete task;

  return 0;
}