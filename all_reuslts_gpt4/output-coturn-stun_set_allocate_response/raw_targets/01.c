#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "stun.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  _stun_buffer buf;
  stun_tid tid;
  ioa_addr relayed_addr1;
  ioa_addr relayed_addr2;
  ioa_addr reflexive_addr;

  int lifetime = provider.ConsumeIntegral<int>();
  int max_lifetime = provider.ConsumeIntegral<int>();
  int error_code = provider.ConsumeIntegral<int>();

  std::string reason = provider.ConsumeRandomLengthString();
  size_t reservation_token = provider.ConsumeIntegral<size_t>();

  std::string mobile_id = provider.ConsumeRandomLengthString();

  stun_set_allocate_response(&buf, &tid, &relayed_addr1, &relayed_addr2, &reflexive_addr, lifetime, max_lifetime, error_code, const_cast<char*>(reason.c_str()), reservation_token, const_cast<char*>(mobile_id.c_str()));

  return 0;
}