#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <vector>

#include <openssl/bio.h>
#include <openssl/dsa.h>
#include <openssl/pem.h>

extern "C" {
#include <openssl/err.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a temporary file and write the fuzzed data to it.
  char filename[] = "/tmp/openssl-fuzz-XXXXXX";
  int fd = mkstemp(filename);
  if (fd == -1) {
    std::cerr << "Failed to create temporary file: " << strerror(errno)
              << std::endl;
    return 0;
  }
  close(fd);

  FILE* fp = fopen(filename, "wb");
  if (fp == nullptr) {
    std::cerr << "Failed to open temporary file: " << strerror(errno)
              << std::endl;
    return 0;
  }
  fwrite(data, 1, size, fp);
  fclose(fp);

  // Read the fuzzed data from the temporary file.
  BIO* bio = BIO_new_file(filename, "r");
  if (bio == nullptr) {
    std::cerr << "Failed to create BIO: " << ERR_error_string(ERR_get_error(), nullptr) << std::endl;
    return 0;
  }

  // Attempt to read a DSA private key from the fuzzed data.
  DSA* dsa = PEM_read_DSAPrivateKey(bio, nullptr, nullptr, nullptr);
  if (dsa == nullptr) {
    std::cerr << "Failed to read DSA private key: " << ERR_error_string(ERR_get_error(), nullptr)
              << std::endl;
    BIO_free(bio);
    return 0;
  }

  // Free the DSA structure.
  DSA_free(dsa);

  // Free the BIO.
  BIO_free(bio);

  // Delete the temporary file.
  unlink(filename);

  return 0;
}