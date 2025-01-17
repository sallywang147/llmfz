#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "picotls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the ptls_t structure
  struct st_ptls_t tls;
  
  // Initialize the ptls_buffer_t structure
  struct st_ptls_buffer_t sendbuf;
  ptls_buffer_init(&sendbuf, "", 0);

  // Consume data for the input and inlen
  std::string input = stream.ConsumeRandomLengthString();
  size_t inlen = input.size();

  // Call the function to be fuzzed
  ptls_send(&tls, &sendbuf, const_cast<char*>(input.c_str()), inlen);

  // Cleanup
  ptls_buffer_dispose(&sendbuf);

  return 0;
}