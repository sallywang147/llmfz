#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "ptls/ptls.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t cert_size = stream.ConsumeIntegralInRange<size_t>(0, 1024);
  const std::string cert = stream.ConsumeBytesAsString(cert_size);
  const std::string key = stream.ConsumeBytesAsString(cert_size);

  struct st_ptls_emit_compressed_certificate_t emit_compressed_certificate;
  ptls_init_compressed_certificate(&emit_compressed_certificate, nullptr, 0,
                                   const_cast<char*>(cert.c_str()), cert_size);
  ptls_init_compressed_certificate(&emit_compressed_certificate, nullptr, 0,
                                   const_cast<char*>(key.c_str()), key.size());
  return 0;
}