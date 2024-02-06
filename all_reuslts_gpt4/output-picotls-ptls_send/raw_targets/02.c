#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "picotls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize st_ptls_t
  struct st_ptls_t tls;
  memset(&tls, 0, sizeof(tls));

  // Define and initialize st_ptls_buffer_t
  struct st_ptls_buffer_t sendbuf;
  memset(&sendbuf, 0, sizeof(sendbuf));

  // Extract input string from data
  std::string input = stream.ConsumeRemainingBytesAsString();
  
  // Call the target function
  int ret = ptls_send(&tls, &sendbuf, input.data(), input.size());

  return 0;
}