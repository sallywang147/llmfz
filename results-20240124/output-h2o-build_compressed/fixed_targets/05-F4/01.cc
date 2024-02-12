#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include "h2o.h"
#include "h2o/http2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    h2o_globalconf_t config;
    h2o_config_init(&config);
    h2o_context_t ctx;
    h2o_context_init(&ctx, h2o_evloop_create(), &config);
    initialized = true;
  }
  FuzzedDataProvider stream(data, size);
  const size_t max_cert_size = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  std::vector<uint8_t> certificate(max_cert_size);
  stream.ConsumeBytes<uint8_t>(certificate.data(), certificate.size());
  const size_t max_ocsp_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<uint8_t> ocsp_status(max_ocsp_size);
  stream.ConsumeBytes<uint8_t>(ocsp_status.data(), ocsp_status.size());
  ptls_decompress_certificate_t entry;
  struct st_h2o_iovec_t iov;
  iov.base = reinterpret_cast<char*>(certificate.data());
  iov.len = certificate.size();
  build_compressed(&entry, &iov, 1, reinterpret_cast<char*>(ocsp_status.data()),
                   ocsp_status.size());
  return 0;
}