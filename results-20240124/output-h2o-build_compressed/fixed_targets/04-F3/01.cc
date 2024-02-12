#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include "h2o.h"
#include "h2o/ptls.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> output_buffer(stream.ConsumeIntegral<size_t>());
  size_t output_written = 0;
  auto output = h2o_iovec_init(output_buffer.data(), output_buffer.size());

  std::vector<uint8_t> ocsp_status(stream.ConsumeIntegral<size_t>());
  auto ocsp = h2o_iovec_init(ocsp_status.data(), ocsp_status.size());

  struct st_ptls_compressed_certificate_entry_t compressed_entry;
  int ret = build_compressed(&compressed_entry, &output, output_written, ocsp.base, ocsp.len);
  if (ret != 0) {
    return 0;
  }

  return 0;
}