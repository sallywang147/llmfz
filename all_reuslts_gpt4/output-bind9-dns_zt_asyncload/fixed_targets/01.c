#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "dns.h"

// Define a callback function for dns_zt_asyncload
void loaddone(struct dns_zt *zt, int status, void *arg) {
  // Callback function body
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize dns_zt
  struct dns_resolv_conf *resconf;
  struct dns_hosts *hosts;
  struct dns_hints *hints;
  struct dns_zt *zt;

  resconf = dns_resconf_local(&dns_defresconf);
  hosts = dns_hosts_local(&dns_defhosts);
  hints = dns_hints_local(resconf, &dns_defhints);

  zt = dns_zt_init(resconf, hosts, hints);

  if (zt == NULL) {
    return 0;
  }

  // Extract boolean value for newonly
  bool newonly = stream.ConsumeBool();

  // Extract string for arg
  std::string arg = stream.ConsumeRandomLengthString();
  
  // Call the function
  int result = dns_zt_asyncload(zt, newonly, loaddone, (char *)arg.c_str());

  // Clean up
  dns_zt_free(zt);
  dns_hints_free(hints);
  dns_hosts_free(hosts);
  dns_resconf_free(resconf);

  return 0;
}