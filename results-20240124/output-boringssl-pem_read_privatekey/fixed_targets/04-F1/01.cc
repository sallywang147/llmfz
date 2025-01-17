#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <string>

#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const std::string filename = stream.ConsumeRandomLengthString();
  std::ofstream file(filename);
  file << stream;
  file.close();

  BIO* bio = BIO_new_file(filename.c_str(), "r");
  if (bio == nullptr) {
    return 0;
  }

  EVP_PKEY* pkey = nullptr;
  PEM_read_bio_PrivateKey(bio, &pkey, nullptr, nullptr);
  BIO_free(bio);

  EVP_PKEY_free(pkey);

  return 0;
}