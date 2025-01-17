 #include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

#include <openssl/bio.h>
#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/pem.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::string input_string = stream.ConsumeRemainingBytesAsString();
  BIO* bio = BIO_new(BIO_s_mem());
  BIO_write(bio, input_string.c_str(), input_string.size());

  EC_KEY* key = nullptr;
  PEM_read_bio_ECPrivateKey(bio, &key, nullptr, nullptr);
  if (key != nullptr) {
    EC_KEY_free(key);
  }

  BIO_free(bio);
  return 0;
}