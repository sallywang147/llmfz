#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "stun.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct _stun_buffer* buf = (struct _stun_buffer*)stream.ConsumeBytes<uint8_t>(
      stream.ConsumeIntegralInRange<size_t>(0, size));
  struct stun_tid* tid = (struct stun_tid*)stream.ConsumeBytes<uint8_t>(
      stream.ConsumeIntegralInRange<size_t>(0, size));
  union ioa_addr* relayed_addr1 = (union ioa_addr*)stream.ConsumeBytes<uint8_t>(
      stream.ConsumeIntegralInRange<size_t>(0, size));
  union ioa_addr* relayed_addr2 = (union ioa_addr*)stream.ConsumeBytes<uint8_t>(
      stream.ConsumeIntegralInRange<size_t>(0, size));
  union ioa_addr* reflexive_addr = (union ioa_addr*)stream.ConsumeBytes<uint8_t>(
      stream.ConsumeIntegralInRange<size_t>(0, size));
  const int lifetime = stream.ConsumeIntegral<int>();
  const int max_lifetime = stream.ConsumeIntegral<int>();
  const int error_code = stream.ConsumeIntegral<int>();
  const std::string reason = stream.ConsumeRemainingBytesAsString();
  const size_t reservation_token = stream.ConsumeIntegral<size_t>();
  const std::string mobile_id = stream.ConsumeRemainingBytesAsString();

  stun_set_allocate_response(buf, tid, relayed_addr1, relayed_addr2,
                             reflexive_addr, lifetime, max_lifetime, error_code,
                             reason.c_str(), reservation_token,
                             mobile_id.c_str());
  return 0;
}