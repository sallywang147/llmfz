#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "wget.h"

extern "C" {
#include "wget.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct wget_tcp_st tcp;
  memset(&tcp, 0, sizeof(tcp));

  std::string format = stream.ConsumeRemainingBytesAsString();
  size_t ret = wget_tcp_printf(&tcp, format.c_str());
  return 0;
}