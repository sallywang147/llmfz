#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" {
#include <ssh/recv_msg_userauth_pk_ok.h>
}

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
  int result = recv_msg_userauth_pk_ok(public_key.data(), public_key.size(), signature.data(),
                         signature.size(), algorithm_name.c_str());

  // Check the return value of the function.
  if (result != 0) {
    // An error occurred.
    // Handle the error here.
  }

  return 0;
}

// Definition of the function recv_msg_userauth_pk_ok.
int recv_msg_userauth_pk_ok(const uint8_t* public_key, size_t public_key_len,
                           const uint8_t* signature, size_t signature_len,
                           const char* algorithm_name) {
  // Implement the function here.
  return 0;
}