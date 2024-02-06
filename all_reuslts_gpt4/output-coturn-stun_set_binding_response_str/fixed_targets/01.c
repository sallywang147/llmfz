#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "stun.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize parameters for stun_set_binding_response_str
  char buf[1024];
  size_t len = sizeof(buf);
  struct stun_tid tid;
  union.ioa_addr reflexive_addr;
  int error_code = stream.ConsumeIntegral<int>();
  char reason[256];
  int cookie = stream.ConsumeIntegral<int>();
  int old_stun = stream.ConsumeIntegral<int>();
  int no_stun_backward_compatibility = stream.ConsumeIntegral<int>();

  // Consume data for tid and reflexive_addr
  if (stream.remaining_bytes() < sizeof(tid) + sizeof(reflexive_addr)) {
    return 0;
  }
  stream.ConsumeData(&tid, sizeof(tid));
  stream.ConsumeData(&reflexive_addr, sizeof(reflexive_addr));

  // Consume string for reason
  std::string reason_str = stream.ConsumeRandomLengthString();
  strncpy(reason, reason_str.c_str(), sizeof(reason) - 1);
  reason[sizeof(reason) - 1] = '\0';

  // Call the function with the parameters
  stun_set_binding_response_str(buf, &len, &tid, &reflexive_addr, error_code, reason, cookie, old_stun, no_stun_backward_compatibility);

  return 0;
}