#include <fuzzer/FuzzedDataProvider.h>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wget.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  
  // Initialize the tcp structure
  struct wget_tcp_st tcp;
  tcp.sockfd = fdp.ConsumeIntegral<int>();
  tcp.family = fdp.ConsumeIntegral<int>();
  tcp.local_addrinfo = NULL;
  tcp.remote_addrinfo = NULL;
  tcp.bind_addr = NULL;
  tcp.dns_cache = NULL;
  tcp.caching = fdp.ConsumeBool();
  tcp.print = NULL;

  // Generate format string and arguments
  std::string fmt = fdp.ConsumeRandomLengthString();
  va_list args;
  va_start(args, fmt.c_str());
  
  // Call the function
  wget_tcp_vprintf(&tcp, fmt.c_str(), args);
  
  va_end(args);
  
  return 0;
}