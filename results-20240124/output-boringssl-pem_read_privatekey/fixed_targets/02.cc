 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include <openssl/pem.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  // Create a temporary file.
  FILE* file = tmpfile();
  if (file == nullptr) {
    return 0;
  }
  // Write the fuzzed data to the temporary file.
  size_t written = fwrite(data, 1, size, file);
  if (written != size) {
    fclose(file);
    return 0;
  }
  // Rewind the file pointer to the beginning of the file.
  rewind(file);
  // Read the private key from the temporary file.
  struct evp_pkey_st* key = PEM_read_PrivateKey(file, nullptr, nullptr, nullptr);
  // Close the temporary file.
  fclose(file);
  // Free the private key.
  EVP_PKEY_free(key);
  return 0;
}