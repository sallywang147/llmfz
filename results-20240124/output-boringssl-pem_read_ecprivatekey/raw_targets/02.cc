 #include <fuzzer/FuzzedDataProvider.h>

#include <openssl/ec.h>
#include <openssl/pem.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  BIO* bio = BIO_new_mem_buf(data, size);
  PEM_read_ECPrivateKey(bio, nullptr, nullptr, nullptr);
  BIO_free(bio);
  return 0;
}