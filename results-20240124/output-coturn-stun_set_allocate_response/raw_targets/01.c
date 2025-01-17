 #include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "fuzzer/FuzzedDataProvider.h"
#include "stun_buffer.h"
#include "stun_tid.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct _stun_buffer* buf = new struct _stun_buffer;
  stun_buffer_init(buf);

  struct stun_tid* tid = new struct stun_tid;
  stun_tid_init(tid);

  union ioa_addr* relayed_addr1 = new union ioa_addr;
  ioa_addr_init(relayed_addr1);

  union ioa_addr* relayed_addr2 = new union ioa_addr;
  ioa_addr_init(relayed_addr2);

  union ioa_addr* reflexive_addr = new union ioa_addr;
  ioa_addr_init(reflexive_addr);

  int lifetime = stream.ConsumeIntegral<int>();
  int max_lifetime = stream.ConsumeIntegral<int>();
  int error_code = stream.ConsumeIntegral<int>();

  const size_t reason_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* reason = new char[reason_size];
  stream.ConsumeBytes(reason, reason_size);

  const size_t reservation_token = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* mobile_id = new char[reservation_token];
  stream.ConsumeBytes(mobile_id, reservation_token);

  stun_set_allocate_response(buf, tid, relayed_addr1, relayed_addr2, reflexive_addr, lifetime, max_lifetime, error_code, reason, reservation_token, mobile_id);

  stun_buffer_free(buf);
  stun_tid_free(tid);
  ioa_addr_free(relayed_addr1);
  ioa_addr_free(relayed_addr2);
  ioa_addr_free(reflexive_addr);
  delete[] reason;
  delete[] mobile_id;

  return 0;
}