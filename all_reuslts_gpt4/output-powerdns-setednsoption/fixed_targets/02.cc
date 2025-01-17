#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "dnsquestion.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  // Initialize a DNSQuestion object
  struct DNSQuestion dnsQuestion;

  // Consume data for the short parameter
  short shortParam = provider.ConsumeIntegral<short>();

  // Consume data for the string parameter
  std::string stringParam = provider.ConsumeRemainingBytesAsString();

  // Call the target function
  bool result = setEDNSOption(&dnsQuestion, shortParam, &stringParam);

  return 0;
}