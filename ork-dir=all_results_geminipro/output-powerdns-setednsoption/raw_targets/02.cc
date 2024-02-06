#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "packetcache.hh"
#include "statbag.hh"

StatBag S;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size > std::numeric_limits<uint16_t>::max() || size < sizeof(dnsheader)) {
    return 0;
  }

  std::string input(reinterpret_cast<const char *>(data), size);
  DNSQuestion q;
  std::string opt;

  FuzzedDataProvider provider(data, size);

  auto code = provider.ConsumeIntegralInRange<uint16_t>(0, 0xFFFF);
  auto length = provider.ConsumeIntegralInRange<uint16_t>(0, 0xFFFF);
  auto data_size = provider.ConsumeIntegralInRange<size_t>(0, 0xFFFF);
  if (data_size > provider.remaining_bytes()) {
    data_size = provider.remaining_bytes();
  }
  auto data = provider.ConsumeBytes<uint8_t>(data_size);

  setEDNSOption(&q, code, &opt);

  return 0;
}