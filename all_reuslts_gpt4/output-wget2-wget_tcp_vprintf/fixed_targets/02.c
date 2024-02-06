#include <fuzzer/FuzzedDataProvider.h>
#include <cstdarg>
#include <cstdio>
#include <vector>
#include "wget.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize a wget_tcp_st structure
  wget_tcp_st tcp;
  tcp.sockfd = -1;
  tcp.family = stream.ConsumeIntegral<unsigned short>();
  tcp.passive = stream.ConsumeBool();
  tcp.local_bind = stream.ConsumeBool();
  tcp.print = stream.ConsumeBool();
  tcp.caching = stream.ConsumeBool();
  tcp.ssl = stream.ConsumeBool();
  tcp.connect_timeout = stream.ConsumeIntegral<int>();
  tcp.timeout = stream.ConsumeIntegral<int>();

  // Extract a string to be used as the format string for vprintf
  std::string fmt = stream.ConsumeRemainingBytesAsString();

  // Initialize a va_list and call the target function
  va_list args;
  va_start(args, fmt.c_str());
  wget_tcp_vprintf(&tcp, const_cast<char *>(fmt.c_str()), args);
  va_end(args);

  return 0;
}