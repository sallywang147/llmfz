#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <gnutls/gnutls.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string session_data = stream.ConsumeRemainingBytesAsString();
  const size_t session_data_size = session_data.size();
  gnutls_session_int* session = nullptr;
  size_t actual_session_data_size = 0;
  int ret = gnutls_session_get_data(session,
                                    reinterpret_cast<char*>(
                                        const_cast<char*>(session_data.c_str())),
                                    &actual_session_data_size);
  if (ret != 0) {
    return 0;
  }
  return 0;
}