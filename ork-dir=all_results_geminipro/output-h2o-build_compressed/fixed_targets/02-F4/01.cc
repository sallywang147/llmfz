#include <fuzzer/FuzzedDataProvider.h>
#include <h2o/mem.h>
#include <h2o/string_.h>
#include <ptls/compression.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::vector<uint8_t> compressed_certificate_entry(
      stream.ConsumeIntegralInRange<size_t>(0, 1024));
  stream.ConsumeBytes<uint8_t>(compressed_certificate_entry.data(),
                               compressed_certificate_entry.size());

  std::vector<uint8_t> iovec_data(stream.ConsumeIntegralInRange<size_t>(0, 1024));
  stream.ConsumeBytes<uint8_t>(iovec_data.data(), iovec_data.size());

  struct st_h2o_iovec_t iovec;
  iovec.base = iovec_data.data();
  iovec.len = iovec_data.size();

  std::vector<uint8_t> ocsp_status(stream.ConsumeIntegralInRange<size_t>(0, 1024));
  stream.ConsumeBytes<uint8_t>(ocsp_status.data(), ocsp_status.size());

  struct st_ptls_compressed_certificate_entry_t compressed_certificate_entry_struct;
  memset(&compressed_certificate_entry_struct, 0,
         sizeof(compressed_certificate_entry_struct));

  ptls_build_compressed_certificate_entry(&compressed_certificate_entry_struct, &iovec,
                                          compressed_certificate_entry.size(),
                                          reinterpret_cast<char*>(ocsp_status.data()),
                                          ocsp_status.size());

  return 0;
}