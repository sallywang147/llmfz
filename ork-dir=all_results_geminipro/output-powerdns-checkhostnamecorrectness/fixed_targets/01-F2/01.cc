#include "packetcache.hh"
#include "statbag.hh"

extern "C" {
#include "dns.h"
}

StatBag S;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {

  if (size > std::numeric_limits<uint16_t>::max() || size < sizeof(dnsheader)) {
    return 0;
  }

  std::string input(reinterpret_cast<const char *>(data), size);

  /* auth's version */
  try {
    static const std::unordered_set<uint16_t> optionsToIgnore{EDNSOptionCode::COOKIE};

    PacketCache::canHashPacket(input, optionsToIgnore);
    DNSResourceRecord r(input.data(), input.size(), sizeof(dnsheader), false);
    checkHostnameCorrectness(&r);
    PacketCache::queryMatches(input, input, r.qname, optionsToIgnore);
  } catch (const std::exception &e) {
  } catch (const PDNSException &e) {
  }

  /* recursor's version */
  try {
    static const std::unordered_set<uint16_t> optionsToIgnore{EDNSOptionCode::COOKIE, EDNSOptionCode::ECS};

    PacketCache::canHashPacket(input, optionsToIgnore);
    DNSResourceRecord r(input.data(), input.size(), sizeof(dnsheader), false);
    checkHostnameCorrectness(&r);
    PacketCache::queryMatches(input, input, r.qname, optionsToIgnore);
  } catch (const std::exception &e) {
  } catch (const PDNSException &e) {
  }

  return 0;
}