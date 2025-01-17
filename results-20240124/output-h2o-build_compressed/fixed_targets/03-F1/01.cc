#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "common.h"
#include "ptls.h"
#include "ptls_compression.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct st_ptls_compressed_certificate_entry_t compressed;
  struct st_h2o_iovec_t iov;
  char ocsp_status[1024];
  size_t ocsp_status_len = stream.ConsumeIntegralInRange<size_t>(0, 1024);

  stream.ConsumeBytes<char>(ocsp_status, ocsp_status_len);
  build_compressed(&compressed, &iov, 0, ocsp_status, ocsp_status_len);
  return 0;
}