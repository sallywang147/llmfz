 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <openssl/bio.h>
#include <openssl/ec.h>
#include <openssl/pem.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string pem_string = stream.ConsumeRemainingBytesAsString();
  BIO* bio = BIO_new_mem_buf(pem_string.c_str(), pem_string.size());
  if (bio == nullptr) {
    return 0;
  }

  EC_KEY* ec_key = nullptr;
  PEM_read_bio_ECPrivateKey(bio, &ec_key, nullptr, nullptr);
  BIO_free(bio);
  EC_KEY_free(ec_key);

  return 0;
}