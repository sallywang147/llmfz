#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "stun.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t buf_size = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  char* buf = new char[buf_size];
  size_t* len = new size_t;
  *len = buf_size;

  stun_tid* tid = new stun_tid;
  tid->id[0] = stream.ConsumeIntegralInRange<uint8_t>(0, 255);
  tid->id[1] = stream.ConsumeIntegralInRange<uint8_t>(0, 255);
  tid->id[2] = stream.ConsumeIntegralInRange<uint8_t>(0, 255);
  tid->id[3] = stream.ConsumeIntegralInRange<uint8_t>(0, 255);
  tid->id[4] = stream.ConsumeIntegralInRange<uint8_t>(0, 255);
  tid->id[5] = stream.ConsumeIntegralInRange<uint8_t>(0, 255);
  tid->id[6] = stream.ConsumeIntegralInRange<uint8_t>(0, 255);
  tid->id[7] = stream.ConsumeIntegralInRange<uint8_t>(0, 255);

  ioa_addr* relayed_addr1 = new ioa_addr;
  relayed_addr1->ipv4.s_addr = stream.ConsumeIntegral<uint32_t>();
  relayed_addr1->ipv6.s6_addr = stream.ConsumeIntegral<uint64_t>();
  relayed_addr1->ipv6.s6_addr32[0] = stream.ConsumeIntegral<uint32_t>();
  relayed_addr1->ipv6.s6_addr32[1] = stream.ConsumeIntegral<uint32_t>();
  relayed_addr1->ipv6.s6_addr32[2] = stream.ConsumeIntegral<uint32_t>();
  relayed_addr1->ipv6.s6_addr32[3] = stream.ConsumeIntegral<uint32_t>();

  ioa_addr* relayed_addr2 = new ioa_addr;
  relayed_addr2->ipv4.s_addr = stream.ConsumeIntegral<uint32_t>();
  relayed_addr2->ipv6.s6_addr = stream.ConsumeIntegral<uint64_t>();
  relayed_addr2->ipv6.s6_addr32[0] = stream.ConsumeIntegral<uint32_t>();
  relayed_addr2->ipv6.s6_addr32[1] = stream.ConsumeIntegral<uint32_t>();
  relayed_addr2->ipv6.s6_addr32[2] = stream.ConsumeIntegral<uint32_t>();
  relayed_addr2->ipv6.s6_addr32[3] = stream.ConsumeIntegral<uint32_t>();

  ioa_addr* reflexive_addr = new ioa_addr;
  reflexive_addr->ipv4.s_addr = stream.ConsumeIntegral<uint32_t>();
  reflexive_addr->ipv6.s6_addr = stream.ConsumeIntegral<uint64_t>();
  reflexive_addr->ipv6.s6_addr32[0] = stream.ConsumeIntegral<uint32_t>();
  reflexive_addr->ipv6.s6_addr32[1] = stream.ConsumeIntegral<uint32_t>();
  reflexive_addr->ipv6.s6_addr32[2] = stream.ConsumeIntegral<uint32_t>();
  reflexive_addr->ipv6.s6_addr32[3] = stream.ConsumeIntegral<uint32_t>();

  const int lifetime = stream.ConsumeIntegral<int>();
  const int max_lifetime = stream.ConsumeIntegral<int>();
  const int error_code = stream.ConsumeIntegral<int>();

  const std::string reason = stream.ConsumeRemainingBytesAsString();

  const size_t reservation_token = stream.ConsumeIntegral<size_t>();

  const std::string mobile_id = stream.ConsumeRemainingBytesAsString();

  const int ret = stun_set_allocate_response_str(buf, len, tid, relayed_addr1,
                                               relayed_addr2, reflexive_addr,
                                               lifetime, max_lifetime, error_code,
                                               reason.c_str(), reservation_token,
                                               mobile_id.c_str());
  delete[] buf;
  delete len;
  delete tid;
  delete relayed_addr1;
  delete relayed_addr2;
  delete reflexive_addr;
  return ret;
}