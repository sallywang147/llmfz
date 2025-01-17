#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Consume the public key.
  std::vector<uint8_t> public_key = provider.ConsumeBytes<uint8_t>(
      provider.ConsumeIntegralInRange<size_t>(0, size));

  // Consume the signature.
  std::vector<uint8_t> signature = provider.ConsumeBytes<uint8_t>(
      provider.ConsumeIntegralInRange<size_t>(0, size));

  // Consume the algorithm name.
  std::string algorithm_name = provider.ConsumeRandomLengthString();

  // Call the function under test.
  recv_msg_userauth_pk_ok(public_key.data(), public_key.size(), signature.data(),
                         signature.size(), algorithm_name.c_str());

  return 0;
}