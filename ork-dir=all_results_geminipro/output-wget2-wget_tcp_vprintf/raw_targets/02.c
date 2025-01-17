#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "wget.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string fmt = stream.ConsumeRemainingBytesAsString();

  struct wget_tcp_st tcp;
  wget_tcp_init(&tcp);

  // Initialize va_list.
  va_list args;
  va_start(args, fmt.c_str());

  wget_tcp_vprintf(&tcp, const_cast<char*>(fmt.c_str()), &args);

  va_end(args);
  wget_tcp_close(&tcp);
  return 0;
}