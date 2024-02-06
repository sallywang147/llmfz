#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" void levent_update_and_send(int fd, short what, char * arg);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int fd = stream.ConsumeIntegral<int>();
  short what = stream.ConsumeIntegral<short>();
  std::string arg = stream.ConsumeRemainingBytesAsString();

  levent_update_and_send(fd, what, const_cast<char*>(arg.c_str()));

  return 0;
}