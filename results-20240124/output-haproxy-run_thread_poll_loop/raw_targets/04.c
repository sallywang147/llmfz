 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" char* run_thread_poll_loop(char * data) {
  FuzzedDataProvider stream(data, 0);
  return run_thread_poll_loop(stream.ConsumeRemainingBytesAsString().c_str());
}