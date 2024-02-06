#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <string>
#include "dns.h" // Assuming this is the header file where DNSQuestion and setEDNSOption are defined

struct DNSQuestion {
  // Assuming some structure
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  DNSQuestion dnsQuestion; // Assuming DNSQuestion doesn't require any particular initialization
  short optionCode = stream.ConsumeIntegral<short>();
  std::string optionData = stream.ConsumeRemainingBytesAsString();

  setEDNSOption(&dnsQuestion, optionCode, &optionData);

  return 0;
}