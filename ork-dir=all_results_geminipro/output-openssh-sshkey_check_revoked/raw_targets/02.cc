#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "sshkey.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string key_string = stream.ConsumeRemainingBytesAsString();

  sshkey *key = sshkey_new(key_string.c_str());
  if (key == nullptr) {
    return 0;
  }

  const std::string revoked_keys_file = stream.ConsumeRemainingBytesAsString();

  int result = sshkey_check_revoked(key, const_cast<char*>(revoked_keys_file.c_str()));

  sshkey_free(key);

  return result;
}