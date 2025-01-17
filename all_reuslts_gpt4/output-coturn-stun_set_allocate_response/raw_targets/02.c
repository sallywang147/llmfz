#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "stun_protocol.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct _stun_buffer buf;
  struct stun_tid tid;
  union.ioa_addr relayed_addr1;
  union.ioa_addr relayed_addr2;
  union.ioa_addr reflexive_addr;
  int lifetime = stream.ConsumeIntegral<int>();
  int max_lifetime = stream.ConsumeIntegral<int>();
  int error_code = stream.ConsumeIntegral<int>();

  std::string reason = stream.ConsumeRandomLengthString();
  char * reason_ptr = const_cast<char*>(reason.c_str());

  size_t reservation_token = stream.ConsumeIntegral<size_t>();

  std::string mobile_id = stream.ConsumeRandomLengthString();
  char * mobile_id_ptr = const_cast<char*>(mobile_id.c_str());

  stun_set_allocate_response(&buf, &tid, &relayed_addr1, &relayed_addr2, &reflexive_addr, lifetime, max_lifetime, error_code, reason_ptr, reservation_token, mobile_id_ptr);

  return 0;
}