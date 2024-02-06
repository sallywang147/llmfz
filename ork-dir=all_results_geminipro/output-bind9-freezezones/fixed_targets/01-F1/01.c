#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include "dns.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string zone_name = stream.ConsumeRemainingBytesAsString();

  struct dns_zone zone;
  memset(&zone, 0, sizeof(zone));
  zone.name = const_cast<char*>(zone_name.c_str());
  zone.soa = &zone.soa_rec;
  zone.soa_rec.serial = 1;
  zone.soa_rec.rname = const_cast<char*>("ns.example.com.");
  zone.soa_rec.mname = const_cast<char*>("ns.example.com.");
  zone.soa_rec.refresh = 86400;
  zone.soa_rec.retry = 7200;
  zone.soa_rec.expire = 1209600;
  zone.soa_rec.minimum = 3600;

  std::vector<char> uap_buffer(stream.ConsumeIntegralInRange<size_t>(0, 1024));
  char* uap = uap_buffer.data();
  stream.ConsumeBytes(uap, uap_buffer.size());

  freezezones(&zone, uap);
  return 0;
}