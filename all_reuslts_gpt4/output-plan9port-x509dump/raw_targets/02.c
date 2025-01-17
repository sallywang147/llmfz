#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume data for the certificate
  size_t ncert = stream.ConsumeIntegralInRange<int>(0, size);
  std::string cert = stream.ConsumeBytesAsString(ncert);

  // Call the function under test
  X509dump(const_cast<char*>(cert.c_str()), ncert);

  return 0;
}