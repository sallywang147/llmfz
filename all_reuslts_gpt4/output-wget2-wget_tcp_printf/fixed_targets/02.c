#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wget.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct wget_tcp_st tcp;
  std::string fmt = stream.ConsumeRemainingBytesAsString();
  
  wget_tcp_printf(&tcp, fmt.c_str());

  return 0;
}