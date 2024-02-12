#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

#include "h2o.h"
#include "h2o/http2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t compressed_certificate_entry_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct st_ptls_compressed_certificate_entry_t {
    uint8_t data[1024];  // Change to a fixed size
  } compressed_certificate_entry;
  const size_t output_buffer_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  struct st_h2o_iovec_t output_buffer;
  output_buffer.base = stream.ConsumeBytes<char>(output_buffer_size).data();
  output_buffer.len = output_buffer_size;
  const size_t ocsp_status_size =
      stream.ConsumeIntegralInRange<size_t>(0, 1024);
  std::vector<char> ocsp_status(ocsp_status_size);
  memcpy(&ocsp_status[0], stream.ConsumeBytes<char>(ocsp_status_size).data(), ocsp_status_size);  // Use memcpy instead of copy
  build_compressed(&compressed_certificate_entry, &output_buffer,
                   compressed_certificate_entry_size, ocsp_status.data(),
                   ocsp_status_size);
  return 0;
}