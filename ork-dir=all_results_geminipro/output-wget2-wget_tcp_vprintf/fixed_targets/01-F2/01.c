#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include "wget.h"
#include "wget_tcp.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct wget_tcp_st tcp;
  wget_tcp_init(&tcp);

  const std::string format = stream.ConsumeRemainingBytesAsString();
  const char* format_c_str = format.c_str();

  va_list args;
  va_start(args, format_c_str);
  wget_tcp_vprintf(&tcp, const_cast<char*>(format_c_str), &args);
  va_end(args);

  wget_tcp_close(&tcp);

  return 0;
}