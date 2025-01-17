#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Read the username.
  std::string username = provider.ConsumeRandomLengthString(16);

  // Read the service name.
  std::string service_name = provider.ConsumeRandomLengthString(16);

  // Read the public key.
  std::vector<uint8_t> public_key = provider.ConsumeBytes<uint8_t>(provider.ConsumeIntegralInRange<size_t>(0, 1024));

  // Read the signature.
  std::vector<uint8_t> signature = provider.ConsumeBytes<uint8_t>(provider.ConsumeIntegralInRange<size_t>(0, 1024));

  // Call the function under test.
  recv_msg_userauth_pk_ok(username.c_str(), service_name.c_str(), public_key.data(), public_key.size(), signature.data(), signature.size());

  return 0;
}