#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "dns.hh"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  DNSResourceRecord dnsResourceRecord;

  dnsResourceRecord.d_place = static_cast<DNSResourceRecord::Place>(stream.ConsumeIntegralInRange<int>(0, 3));
  dnsResourceRecord.d_type = stream.ConsumeIntegral<uint16_t>();
  dnsResourceRecord.d_class = stream.ConsumeIntegral<uint16_t>();
  dnsResourceRecord.d_ttl = stream.ConsumeIntegral<uint32_t>();
  dnsResourceRecord.d_content = stream.ConsumeRandomLengthString().c_str();

  checkHostnameCorrectness(&dnsResourceRecord);

  return 0;
}