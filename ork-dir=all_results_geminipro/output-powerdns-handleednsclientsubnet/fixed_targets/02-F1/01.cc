#include "dns.hh"
#include "dnsheader.hh"
#include "edns.hh"
#include "fuzzer.hh"

extern "C" {
#include <vector>
#include <string>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < sizeof(dnsheader)) {
    return 0;
  }
  std::vector<uint8_t> input(data, data + size);
  std::vector<uint8_t> output;
  bool rcode;
  std::string error;
  handleEDNSClientSubnet(&output, input.size(), sizeof(dnsheader),
                         input.data(), input.data() + sizeof(dnsheader), false,
                         &error);
  return 0;
}