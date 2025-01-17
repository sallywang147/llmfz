#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "sshkey.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract a string for revoked_keys_file. You MUST use .c_str() to use result as pointer
  std::string revoked_keys_file = stream.ConsumeRandomLengthString();
  
  // Generating a ssh key
  struct sshkey *key;
  int ret = sshkey_generate(KEY_DSA, 1024, &key);
  if (ret != 0) {
    return 0;
  }

  // Call the function to fuzz
  sshkey_check_revoked(key, revoked_keys_file.c_str());

  // Clean up
  sshkey_free(key);

  return 0;
}