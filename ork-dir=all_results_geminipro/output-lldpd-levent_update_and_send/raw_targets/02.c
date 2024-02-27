#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int fd = stream.ConsumeIntegral<int>();
  const short what = stream.ConsumeIntegral<short>();
  const std::string arg = stream.ConsumeRemainingBytesAsString();

  levent_update_and_send(fd, what, const_cast<char*>(arg.c_str()));

  return 0;
}