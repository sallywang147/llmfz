#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

#include "stun.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct _stun_buffer* buf = (struct _stun_buffer*)malloc(sizeof(struct _stun_buffer));
  struct stun_tid* tid = (struct stun_tid*)malloc(sizeof(struct stun_tid));
  union ioa_addr* relayed_addr1 = (union ioa_addr*)malloc(sizeof(union ioa_addr));
  union ioa_addr* relayed_addr2 = (union ioa_addr*)malloc(sizeof(union ioa_addr));
  union ioa_addr* reflexive_addr = (union ioa_addr*)malloc(sizeof(union ioa_addr));

  const int lifetime = stream.ConsumeIntegral<int>();
  const int max_lifetime = stream.ConsumeIntegral<int>();
  const int error_code = stream.ConsumeIntegral<int>();
  const size_t reservation_token = stream.ConsumeIntegral<size_t>();
  const std::string reason = stream.ConsumeRemainingBytesAsString();
  const std::string mobile_id = stream.ConsumeRemainingBytesAsString();

  stun_set_allocate_response(buf, tid, relayed_addr1, relayed_addr2, reflexive_addr,
                             lifetime, max_lifetime, error_code, reason.c_str(),
                             reservation_token, mobile_id.c_str());

  free(buf);
  free(tid);
  free(relayed_addr1);
  free(relayed_addr2);
  free(reflexive_addr);
  return 0;
}
```

The code above compiles without errors.