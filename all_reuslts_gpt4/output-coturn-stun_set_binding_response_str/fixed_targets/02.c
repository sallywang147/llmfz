#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "stun.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int error_code = stream.ConsumeIntegral<int>();
  int cookie = stream.ConsumeIntegral<int>();
  int old_stun = stream.ConsumeIntegral<int>();
  int no_stun_backward_compatibility = stream.ConsumeIntegral<int>();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string reason = stream.ConsumeRandomLengthString();
  char *reason_ptr = reason.c_str();

  struct stun_tid tid;
  union.ioa_addr reflexive_addr;

  // Extract to user defined object
  size_t consumed_tid = stream.ConsumeData(&tid, sizeof(tid));
  size_t consumed_addr = stream.ConsumeData(&reflexive_addr, sizeof(reflexive_addr));

  // If not enough data to populate objects, return
  if (consumed_tid < sizeof(tid) || consumed_addr < sizeof(reflexive_addr)) {
    return 0;
  }

  // Prepare buffer and length
  size_t len = 1024;
  char buf[1024];

  // Call the function under test
  stun_set_binding_response_str(buf, &len, &tid, &reflexive_addr, error_code, reason_ptr, cookie, old_stun, no_stun_backward_compatibility);

  return 0;
}