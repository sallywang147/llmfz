#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "stun/stun.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct _stun_buffer buf;
  struct stun_tid tid;
  union.ioa_addr reflexive_addr;
  int error_code = stream.ConsumeIntegral<int>();
  std::string reason = stream.ConsumeRandomLengthString();

  // Initialize tid and reflexive_addr with random data
  size_t tid_size = stream.ConsumeData(&tid, sizeof(tid));
  size_t reflexive_addr_size = stream.ConsumeData(&reflexive_addr, sizeof(reflexive_addr));

  // Initialize buf with random data
  size_t buf_len = stream.remaining_bytes();
  std::vector<uint8_t> buf_data = stream.ConsumeBytes<uint8_t>(buf_len);
  buf.buf = buf_data.data();
  buf.len = buf_len;

  // Call the function to fuzz
  stun_set_binding_response(&buf, &tid, &reflexive_addr, error_code, reason.c_str());

  return 0;
}