#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>

#include "h2o.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct st_ptls_compressed_certificate_entry_t entry;
  struct st_h2o_iovec_t iovec;

  size_t iovec_len = stream.ConsumeIntegralInRange<size_t>(0, size/2);
  std::vector<char> iovec_data = stream.ConsumeBytes<char>(iovec_len);
  iovec.base = iovec_data.data();
  iovec.len = iovec_len;

  size_t ocsp_status_len = stream.ConsumeIntegralInRange<size_t>(0, size - iovec_len);
  std::vector<char> ocsp_status_data = stream.ConsumeBytes<char>(ocsp_status_len);
  char *ocsp_status = ocsp_status_data.data();

  build_compressed(&entry, &iovec, iovec_len, ocsp_status, ocsp_status_len);

  return 0;
}