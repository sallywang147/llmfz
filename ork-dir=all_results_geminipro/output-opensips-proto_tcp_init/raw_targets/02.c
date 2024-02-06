#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "proto.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string proto_name = stream.ConsumeRemainingBytesAsString();
  struct proto_info pi;
  pi.name = const_cast<char*>(proto_name.c_str());
  proto_tcp_init(&pi);
  return 0;
}