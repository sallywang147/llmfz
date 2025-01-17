#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include <libunwind.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const char* thread_name = stream.ConsumeRandomLengthString().c_str();
  const uint64_t thread_id = stream.ConsumeIntegral<uint64_t>();
  const uint64_t thread_start_ip = stream.ConsumeIntegral<uint64_t>();
  const uint64_t thread_start_sp = stream.ConsumeIntegral<uint64_t>();
  const uint64_t thread_state = stream.ConsumeIntegral<uint64_t>();
  const uint64_t thread_flags = stream.ConsumeIntegral<uint64_t>();
  const uint64_t thread_signal = stream.ConsumeIntegral<uint64_t>();
  const uint64_t thread_error = stream.ConsumeIntegral<uint64_t>();
  const uint64_t thread_priority = stream.ConsumeIntegral<uint64_t>();
  const uint64_t thread_policy = stream.ConsumeIntegral<uint64_t>();
  const uint64_t thread_magic = stream.ConsumeIntegral<uint64_t>();

  struct Dwfl_Thread thread;
  memset(&thread, 0, sizeof(thread));
  thread.dwfl_thread_name = thread_name;
  thread.dwfl_thread_id = thread_id;
  thread.dwfl_thread_start_ip = thread_start_ip;
  thread.dwfl_thread_start_sp = thread_start_sp;
  thread.dwfl_thread_state = thread_state;
  thread.dwfl_thread_flags = thread_flags;
  thread.dwfl_thread_signal = thread_signal;
  thread.dwfl_thread_error = thread_error;
  thread.dwfl_thread_priority = thread_priority;
  thread.dwfl_thread_policy = thread_policy;
  thread.dwfl_thread_magic = thread_magic;

  dwfl_thread_getframes(&thread, nullptr, nullptr);

  return 0;
}