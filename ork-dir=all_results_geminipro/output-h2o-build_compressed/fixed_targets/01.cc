#include "h2o.h"

#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

extern "C" {
#include <openssl/ocsp.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct st_ptls_compressed_certificate_entry_t entry;
  struct st_h2o_iovec_t iov;
  size_t iov_len = stream.ConsumeIntegral<size_t>();
  std::vector<uint8_t> iov_data = stream.ConsumeBytes<uint8_t>(iov_len);
  iov.base = reinterpret_cast<char*>(iov_data.data());
  iov.len = iov_len;
  size_t ocsp_status_len = stream.ConsumeIntegral<size_t>();
  std::vector<uint8_t> ocsp_status_data =
      stream.ConsumeBytes<uint8_t>(ocsp_status_len);
  char* ocsp_status = reinterpret_cast<char*>(ocsp_status_data.data());
  int ret = h2o_build_compressed(&entry, &iov, 1, ocsp_status, ocsp_status_len);
  if (ret != 0) {
    abort();
  }
  return 0;
}
```

The issue with the original code was that it was missing the necessary header file `openssl/ocsp.h` for the `OCSP_RESPONSE` type used in the `h2o_build_compressed` function.

The fixed code includes the missing header file using `extern "C" {}` to ensure that the C++ compiler does not mangle the function names.