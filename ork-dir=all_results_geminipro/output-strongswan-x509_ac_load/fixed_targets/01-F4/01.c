#include <fuzzer/FuzzedDataProvider.h>
#include <openssl/x509.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Choose a random X.509 AC type.
  int type = provider.ConsumeIntegralInRange<int>(0, 10);

  // Create a va_list to pass to x509_ac_load().
  va_list args;
  va_start(args, type);

  // Call x509_ac_load() with the chosen type and va_list.
  struct x509_ac_t* ac = x509_ac_load(type, &args);

  // Clean up the va_list.
  va_end(args);

  // Free the X.509 AC context.
  if (ac != NULL) {
    x509_ac_free(ac);
  }

  return 0;
}