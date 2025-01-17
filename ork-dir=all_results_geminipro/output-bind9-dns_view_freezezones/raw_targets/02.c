#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "ldns/ldns.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string domain_name = stream.ConsumeRemainingBytesAsString();
  ldns_view* view = ldns_view_new(ldns_resolver_new());
  if (view == nullptr) {
    return 0;
  }
  ldns_zone* zone = ldns_zone_new(domain_name.c_str(), ldns_rr_class_IN);
  if (zone == nullptr) {
    ldns_view_free(view);
    return 0;
  }
  ldns_view_add_zone(view, zone);
  const bool value = stream.ConsumeBool();
  dns_view_freezezones(view, value);
  ldns_zone_free(zone);
  ldns_view_free(view);
  return 0;
}