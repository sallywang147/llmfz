#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "h2o.h"
#include "picotls.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the necessary structures
  struct st_ptls_compressed_certificate_entry_t compressed_certificate_entry;
  struct st_h2o_iovec_t iovec;

  // Consume data for the iovec structure
  size_t iovec_len = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes() / 2);
  std::string iovec_str = stream.ConsumeBytesAsString(iovec_len);
  iovec.base = const_cast<char*>(iovec_str.data());
  iovec.len = iovec_str.size();

  // Consume data for the ocsp_status
  size_t ocsp_status_len = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
  std::string ocsp_status_str = stream.ConsumeBytesAsString(ocsp_status_len);
  char *ocsp_status = const_cast<char*>(ocsp_status_str.data());

  // Call the target function
  int result = build_compressed(&compressed_certificate_entry, &iovec, iovec_len, ocsp_status, ocsp_status_len);

  return 0;
}