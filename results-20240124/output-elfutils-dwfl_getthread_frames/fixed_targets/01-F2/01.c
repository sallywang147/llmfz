#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>  // for std::swap
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {  // Wrap the header with extern "C" to fix linking issues
#include <dwfl.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  dwfl_thread_t thread;
  thread.tid = stream.ConsumeIntegral<int>();
  thread.name = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100));
  thread.state = stream.ConsumeIntegral<int>();
  thread.start_time = stream.ConsumeIntegral<uint64_t>();
  thread.user_time = stream.ConsumeIntegral<uint64_t>();
  thread.system_time = stream.ConsumeIntegral<uint64_t>();

  // Fix the call to dwfl_getthread_frames by swapping the arguments
  dwfl_getthread_frames(&thread, nullptr, nullptr, nullptr);
  return 0;
}