#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

#include "h2o.h"
#include "ptls.h"

extern "C" {
#include "ptls_emit_compressed_certificate.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  ptls_emit_compressed_certificate_t* certificate =
      ptls_emit_compressed_certificate_new(nullptr);
  if (certificate == nullptr) {
    return 0;
  }

  const size_t num_iovecs = stream.ConsumeIntegralInRange<size_t>(0, 10);
  std::vector<h2o_iovec_t> iovecs(num_iovecs);
  for (size_t i = 0; i < num_iovecs; ++i) {
    const size_t iovec_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
    iovecs[i].len = iovec_size;
    iovecs[i].base = stream.ConsumeBytes<char>(iovec_size).data();
  }

  const size_t key_size = stream.ConsumeIntegralInRange<size_t>(0, 100);
  char* key = stream.ConsumeBytes<char>(key_size).data();

  const size_t cert_size = stream.ConsumeIntegralInRange<size_t>(0, 1000);
  char* cert = stream.ConsumeBytes<char>(cert_size).data();

  int ret = ptls_init_compressed_certificate(certificate, iovecs.data(),
                                              iovecs.size(), key, cert_size);
  if (ret != 0) {
    ptls_emit_compressed_certificate_free(certificate);
    return 0;
  }

  ptls_emit_compressed_certificate_free(certificate);
  return 0;
}