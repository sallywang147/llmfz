#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "TPM2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the parameters for CryptSecretEncrypt.
  int keyHandle = stream.ConsumeIntegral<int>();
  std::string label = stream.ConsumeRandomLengthString();
  TPM2B_DATA data_param;
  TPM2B_PUBLIC_KEY_RSA secret;

  // Initialize the data_param and secret structures.
  data_param.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(data_param.buffer));
  std::vector<uint8_t> data_buffer = stream.ConsumeBytes<uint8_t>(data_param.size);
  memcpy(data_param.buffer, data_buffer.data(), data_param.size);

  secret.size = stream.ConsumeIntegralInRange<uint16_t>(0, sizeof(secret.buffer));
  std::vector<uint8_t> secret_buffer = stream.ConsumeBytes<uint8_t>(secret.size);
  memcpy(secret.buffer, secret_buffer.data(), secret.size);

  // Call the target function.
  CryptSecretEncrypt(keyHandle, const_cast<char*>(label.c_str()), &data_param, &secret);

  return 0;
}