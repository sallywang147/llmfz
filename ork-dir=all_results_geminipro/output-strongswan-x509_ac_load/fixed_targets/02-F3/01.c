#include <fuzzer/FuzzedDataProvider.h>

#include <openssl/x509.h>

extern "C" {
#include <openssl/x509_ac.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int type = stream.ConsumeIntegral<int>();
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size));
  const unsigned char *data_ptr = bytes.data();

  struct x509_ac_t *x509_ac = x509_ac_load(type, data_ptr);
  if (x509_ac != NULL) {
    x509_ac_free(x509_ac);
  }

  return 0;
}