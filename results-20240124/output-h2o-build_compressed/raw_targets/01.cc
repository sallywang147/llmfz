 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "h2o.h"
#include "h2o/http2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t compressed_cert_len = stream.ConsumeIntegralInRange<size_t>(0, 100);
  struct st_ptls_compressed_certificate_entry_t* compressed_cert =
      static_cast<struct st_ptls_compressed_certificate_entry_t*>(
          malloc(sizeof(struct st_ptls_compressed_certificate_entry_t) +
                 compressed_cert_len));
  compressed_cert->len = compressed_cert_len;
  stream.ConsumeBytes<uint8_t>(compressed_cert->data, compressed_cert_len);

  const size_t ocsp_status_len = stream.ConsumeIntegralInRange<size_t>(0, 100);
  char* ocsp_status = static_cast<char*>(malloc(ocsp_status_len));
  stream.ConsumeBytes<char>(ocsp_status, ocsp_status_len);

  struct st_h2o_iovec_t iovec = {nullptr, 0};
  int ret = build_compressed(compressed_cert, &iovec, 0, ocsp_status, ocsp_status_len);
  free(iovec.base);
  free(compressed_cert);
  free(ocsp_status);

  return ret;
}