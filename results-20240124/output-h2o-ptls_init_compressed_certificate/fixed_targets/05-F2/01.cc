#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>

extern "C" {
#include "h2o.h"
#include "h2o/ptls.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct st_ptls_emit_compressed_certificate_t* cert =
      (struct st_ptls_emit_compressed_certificate_t*)malloc(
          sizeof(struct st_ptls_emit_compressed_certificate_t));
  if (cert == NULL) {
    return 0;
  }
  struct st_h2o_iovec_t* iovec =
      (struct st_h2o_iovec_t*)malloc(sizeof(struct st_h2o_iovec_t));
  if (iovec == NULL) {
    return 0;
  }
  const size_t cert_len = stream.ConsumeIntegralInRange<size_t>(0, size);
  const char* cert_data = stream.ConsumeBytes<char>(cert_len).data();
  const size_t data_len = stream.ConsumeIntegralInRange<size_t>(0, size);
  const char* data_data = stream.ConsumeBytes<char>(data_len).data();
  ptls_init_compressed_certificate(cert, iovec, cert_len,
                                    const_cast<char*>(cert_data), data_len);
  free(cert);
  free(iovec);
  return 0;
}