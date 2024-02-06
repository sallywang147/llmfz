#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wget.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct wget_tcp_st tcp;
  memset(&tcp, 0, sizeof(tcp));

  FuzzedDataProvider stream(data, size);

  // Extract a string
  std::string str = stream.ConsumeRemainingBytesAsString();
  char *fmt = const_cast<char*>(str.c_str());

  // Call the function to fuzz
  wget_tcp_printf(&tcp, fmt);

  return 0;
}