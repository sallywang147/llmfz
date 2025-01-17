#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "picotls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the structures
  struct st_ptls_emit_compressed_certificate_t emit_compressed_certificate;
  struct st_h2o_iovec_t iovec;

  // Consume data for the structures
  size_t num_iovecs = stream.ConsumeIntegral<size_t>();
  char* char_ptr = stream.ConsumeRemainingBytesAsString().c_str();

  // Call the function under test
  int result = ptls_init_compressed_certificate(&emit_compressed_certificate, &iovec, num_iovecs, char_ptr, size);

  return 0;
}