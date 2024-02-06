#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "tpm2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int keyHandle = stream.ConsumeIntegral<int>();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string label = stream.ConsumeRandomLengthString();
  char *label_ptr = const_cast<char*>(label.c_str());

  // Extract to user defined object
  union TPM2B_DATA data_obj;
  size_t consumed = stream.ConsumeData(&data_obj, sizeof(data_obj));

  union TPM2B_PUBLIC_KEY_RSA secret_obj;
  consumed = stream.ConsumeData(&secret_obj, sizeof(secret_obj));

  // Call the target function
  int result = CryptSecretEncrypt(keyHandle, label_ptr, &data_obj, &secret_obj);

  return 0;
}