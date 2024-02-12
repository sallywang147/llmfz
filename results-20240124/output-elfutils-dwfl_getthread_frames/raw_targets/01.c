 #include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dwfl.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  dwfl_thread_t thread;
  thread.tid = stream.ConsumeIntegral<int>();
  thread.name = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, 100));
  thread.state = stream.ConsumeIntegral<int>();
  thread.start_time = stream.ConsumeIntegral<uint64_t>();
  thread.user_time = stream.ConsumeIntegral<uint64_t>();
  thread.system_time = stream.ConsumeIntegral<uint64_t>();

  dwfl_getthread_frames(nullptr, thread.tid, nullptr, nullptr);
  return 0;
}