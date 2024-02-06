#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "stun.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t buf_len = stream.ConsumeIntegralInRange<size_t>(0, 256);
  std::string buf = stream.ConsumeBytesAsString(buf_len);
  size_t len = stream.ConsumeIntegral<size_t>();

  struct stun_tid tid;
  size_t consumed = stream.ConsumeData(&tid, sizeof(tid));

  union.ioa_addr relayed_addr1;
  consumed = stream.ConsumeData(&relayed_addr1, sizeof(relayed_addr1));

  union.ioa_addr relayed_addr2;
  consumed = stream.ConsumeData(&relayed_addr2, sizeof(relayed_addr2));

  union.ioa_addr reflexive_addr;
  consumed = stream.ConsumeData(&reflexive_addr, sizeof(reflexive_addr));

  int lifetime = stream.ConsumeIntegral<int>();
  int max_lifetime = stream.ConsumeIntegral<int>();
  int error_code = stream.ConsumeIntegral<int>();

  size_t reason_len = stream.ConsumeIntegralInRange<size_t>(0, 256);
  std::string reason = stream.ConsumeBytesAsString(reason_len);

  size_t reservation_token = stream.ConsumeIntegral<size_t>();

  size_t mobile_id_len = stream.ConsumeIntegralInRange<size_t>(0, 256);
  std::string mobile_id = stream.ConsumeBytesAsString(mobile_id_len);

  stun_set_allocate_response_str(buf.data(), &len, &tid, &relayed_addr1, &relayed_addr2, &reflexive_addr, lifetime, max_lifetime, error_code, reason.data(), reservation_token, mobile_id.data());

  return 0;
}