 #include <fuzzer/FuzzedDataProvider.h>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dwfl.h>
#include <sys/types.h>
#include <unistd.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  char *arg = stream.ConsumeRemainingBytesAsString().c_str();
  struct Dwfl_Thread thread;

  thread.dwfl = dwfl_begin(0);
  thread.id = stream.ConsumeIntegral<pid_t>();
  thread.name = stream.ConsumeRemainingBytesAsString().c_str();
  thread.regs = nullptr;
  thread.regs_valid = false;
  thread.frames = nullptr;
  thread.frames_count = 0;
  thread.frames_capacity = 0;

  get_one_thread_frames_cb(&thread, arg);

  dwfl_end(thread.dwfl);
  return 0;
}