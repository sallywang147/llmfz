#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "stun.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct _stun_buffer buf;
  struct stun_tid tid;
  union.ioa_addr reflexive_addr;
  int error_code = stream.ConsumeIntegral<int>();
  std::string reason = stream.ConsumeRandomLengthString();

  // Initialize the buffer
  buf.buf = (uint8_t*)stream.ConsumeRemainingBytes<uint8_t>().data();
  buf.len = stream.remaining_bytes();

  // Initialize the transaction ID
  tid.tsx_id = (uint8_t*)stream.ConsumeBytes<uint8_t>(12).data(); // Transaction ID is 12 bytes

  // Initialize the reflexive address
  reflexive_addr.ss.ss_family = AF_INET;
  reflexive_addr.sin.sin_addr.s_addr = stream.ConsumeIntegral<uint32_t>();
  reflexive_addr.sin.sin_port = stream.ConsumeIntegral<uint16_t>();

  stun_set_binding_response(&buf, &tid, &reflexive_addr, error_code, reason.c_str());

  return 0;
}