#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "common/h2o.h"
#include "common/h2o_iovec.h"
#include "common/ptls.h"

extern "C" {
#include "common/ptls_emit_compressed_certificate.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct st_ptls_emit_compressed_certificate_t* cert =
      static_cast<struct st_ptls_emit_compressed_certificate_t*>(
          malloc(sizeof(struct st_ptls_emit_compressed_certificate_t)));
  struct st_h2o_iovec_t* iovec = static_cast<struct st_h2o_iovec_t*>(
      malloc(sizeof(struct st_h2o_iovec_t)));
  const size_t iovec_len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  iovec->len = iovec_len;
  iovec->base = malloc(iovec_len);
  const size_t cert_len = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  char* cert_data = static_cast<char*>(malloc(cert_len));
  stream.ConsumeBytes(cert_data, cert_len);
  int ret = ptls_emit_compressed_certificate(cert, iovec, iovec_len, cert_data,
                                             cert_len);
  free(iovec->base);
  free(iovec);
  free(cert);
  free(cert_data);
  return ret;
}