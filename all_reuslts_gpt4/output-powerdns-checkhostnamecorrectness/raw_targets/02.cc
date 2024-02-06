#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <string>

#include "dns.hh"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  DNSResourceRecord dnsrr;
  dnsrr.d_name = stream.ConsumeRandomLengthString();
  dnsrr.d_type = stream.ConsumeIntegral<uint16_t>();
  dnsrr.d_class = stream.ConsumeIntegral<uint16_t>();
  dnsrr.d_ttl = stream.ConsumeIntegral<uint32_t>();
  dnsrr.d_content = stream.ConsumeRandomLengthString();

  checkHostnameCorrectness(&dnsrr);

  return 0;
}