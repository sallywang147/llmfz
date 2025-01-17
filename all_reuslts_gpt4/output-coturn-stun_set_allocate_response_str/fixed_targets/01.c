#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "stun.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  char buf[256];
  size_t len = sizeof(buf);
  struct stun_tid tid;
  union.ioa_addr relayed_addr1;
  union.ioa_addr relayed_addr2;
  union.ioa_addr reflexive_addr;
  int lifetime = stream.ConsumeIntegral<int>();
  int max_lifetime = stream.ConsumeIntegral<int>();
  int error_code = stream.ConsumeIntegral<int>();
  char reason[256];
  size_t reservation_token = stream.ConsumeIntegral<size_t>();
  char mobile_id[256];

  // Consume data for struct stun_tid
  size_t consumed = stream.ConsumeData(&tid, sizeof(tid));
  if(consumed != sizeof(tid)) return 0;

  // Consume data for union.ioa_addr
  consumed = stream.ConsumeData(&relayed_addr1, sizeof(relayed_addr1));
  if(consumed != sizeof(relayed_addr1)) return 0;

  consumed = stream.ConsumeData(&relayed_addr2, sizeof(relayed_addr2));
  if(consumed != sizeof(relayed_addr2)) return 0;

  consumed = stream.ConsumeData(&reflexive_addr, sizeof(reflexive_addr));
  if(consumed != sizeof(reflexive_addr)) return 0;

  // Consume strings for reason and mobile_id
  std::string reason_str = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, sizeof(reason)-1));
  strncpy(reason, reason_str.c_str(), sizeof(reason));
  reason[sizeof(reason)-1] = '\0'; // Ensure null-termination

  std::string mobile_id_str = stream.ConsumeBytesAsString(stream.ConsumeIntegralInRange(0, sizeof(mobile_id)-1));
  strncpy(mobile_id, mobile_id_str.c_str(), sizeof(mobile_id));
  mobile_id[sizeof(mobile_id)-1] = '\0'; // Ensure null-termination

  stun_set_allocate_response_str(buf, &len, &tid, &relayed_addr1, &relayed_addr2, &reflexive_addr, lifetime, max_lifetime, error_code, reason, reservation_token, mobile_id);

  return 0;
}