#include "packetcache.hh"
#include "statbag.hh"

StatBag S;

extern "C" {
#include <stddef.h>
#include <stdint.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  if (size > std::numeric_limits<uint16_t>::max() || size < sizeof(dnsheader)) {
    return 0;
  }

  std::string input(reinterpret_cast<const char *>(data), size);

  /* auth's version */
  try {
    static const std::unordered_set<uint16_t> optionsToIgnore{EDNSOptionCode::COOKIE};

    PacketCache::canHashPacket(input, optionsToIgnore);
    DNSName qname(input.data(), input.size(), sizeof(dnsheader), false);
    PacketCache::queryMatches(input, input, qname, optionsToIgnore);
  } catch (const std::exception &e) {
  } catch (const PDNSException &e) {
  }

  /* recursor's version */
  try {
    static const std::unordered_set<uint16_t> optionsToIgnore{EDNSOptionCode::COOKIE, EDNSOptionCode::ECS};

    PacketCache::canHashPacket(input, optionsToIgnore);
    DNSName qname(input.data(), input.size(), sizeof(dnsheader), false);
    PacketCache::queryMatches(input, input, qname, optionsToIgnore);
  } catch (const std::exception &e) {
  } catch (const PDNSException &e) {
  }

  /* checkHostnameCorrectness */
  try {
    static const std::unordered_set<uint16_t> optionsToIgnore{EDNSOptionCode::COOKIE, EDNSOptionCode::ECS};

    PacketCache::canHashPacket(input, optionsToIgnore);
    DNSName qname(input.data(), input.size(), sizeof(dnsheader), false);
    PacketCache::queryMatches(input, input, qname, optionsToIgnore);
    DNSResourceRecord record(input.data(), input.size(), sizeof(dnsheader));
    checkHostnameCorrectness(&record);
  } catch (const std::exception &e) {
  } catch (const PDNSException &e) {
  }

  return 0;
}

extern "C" {
  int checkHostnameCorrectness(const DNSResourceRecord *record) {
    return 0;
  }
}
```
The code was missing the implementation of the function `checkHostnameCorrectness`.
To fix the issue, the function is implemented and wrapped with `extern "C" {}` to allow the object linking to succeed.