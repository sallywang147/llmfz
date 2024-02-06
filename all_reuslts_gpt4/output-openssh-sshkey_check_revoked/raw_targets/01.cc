#include <fuzzer/FuzzedDataProvider.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sshkey.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Generate a temporary file with random content to simulate a revoked keys file.
  char filename[] = "/tmp/fuzz-XXXXXX";
  int fd = mkstemp(filename);
  if (fd < 0) {
    return 0;
  }

  const std::string revoked_keys_content = stream.ConsumeRandomLengthString();
  write(fd, revoked_keys_content.c_str(), revoked_keys_content.size());
  close(fd);

  // Generate a random ssh key.
  struct sshkey *key = sshkey_new(KEY_UNSPEC);
  if (key == nullptr) {
    unlink(filename);
    return 0;
  }

  // Use the temporary file as the revoked keys file.
  sshkey_check_revoked(key, filename);

  sshkey_free(key);
  unlink(filename);

  return 0;
}