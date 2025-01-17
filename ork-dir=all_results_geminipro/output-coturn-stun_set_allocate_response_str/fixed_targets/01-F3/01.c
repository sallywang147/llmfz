#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

extern "C" {
#include "stun.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t buffer_size = stream.ConsumeIntegral<size_t>();
  char* buffer = new char[buffer_size];
  size_t* buffer_length = new size_t;
  *buffer_length = buffer_size;
  struct stun_tid tid;
  union ioa_addr relayed_addr1;
  union ioa_addr relayed_addr2;
  union ioa_addr reflexive_addr;
  const int lifetime = stream.ConsumeIntegral<int>();
  const int max_lifetime = stream.ConsumeIntegral<int>();
  const int error_code = stream.ConsumeIntegral<int>();
  const std::string reason = stream.ConsumeRemainingBytesAsString();
  const size_t reservation_token = stream.ConsumeIntegral<size_t>();
  const std::string mobile_id = stream.ConsumeRemainingBytesAsString();

  const int result = stun_set_allocate_response_str(
      buffer, buffer_length, &tid, &relayed_addr1, &relayed_addr2,
      &reflexive_addr, lifetime, max_lifetime, error_code, reason.c_str(),
      reservation_token, mobile_id.c_str());
  if (result == -1) {
    return 0;
  }
  delete[] buffer;
  delete buffer_length;
  return 0;
}