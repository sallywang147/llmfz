#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" char * run_thread_poll_loop(char * data) {
  FuzzedDataProvider stream((const uint8_t *)data, strlen(data));
  const std::string input = stream.ConsumeRemainingBytesAsString();
  return strdup(input.c_str());
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  run_thread_poll_loop((char *)data);
  return 0;
}