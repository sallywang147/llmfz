#include <string>
#include <unordered_map>
#include <vector>

extern "C" {
#include "clearDNSPacketRecordTypes.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  std::vector<std::string> v;
  std::unordered_map<std::string, std::string> m;
  clearDNSPacketRecordTypes(&v, &m);
  return 0;
}