#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

extern "C" char *run_thread_poll_loop(char *data);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *ptr = const_cast<char *>(str.c_str());
  run_thread_poll_loop(ptr);
  return 0;
}