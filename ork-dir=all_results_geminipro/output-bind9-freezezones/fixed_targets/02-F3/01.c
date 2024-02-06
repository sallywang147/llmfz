#include <fuzzer/FuzzedDataProvider.h>
#include <stdio.h>
#include <stdlib.h>
#include <dns/freezezones.h>

extern "C" {
#include <dns.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  std::vector<uint8_t> zone_data = stream.ConsumeRemainingBytes();
  struct dns_zone* zone = dns_zone_new();
  dns_zone_from_data(zone, zone_data.data(), zone_data.size());

  std::string uap_str = stream.ConsumeRemainingBytesAsString();
  char* uap = strdup(uap_str.c_str());
  int result = freezezones(zone, uap);
  dns_zone_free(zone);
  free(uap);
  return result;
}