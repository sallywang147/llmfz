 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" char* run_thread_poll_loop(char* data) {
  FuzzedDataProvider stream(data, 1000);
  char* fuzzed_data = stream.ConsumeBytesAsString(1000).c_str();

  return run_thread_poll_loop(fuzzed_data);
}