#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>

#include "libfuzzer/libfuzzer_macro.h"
#include "dns/dns.hh"
#include "packetcache.hh"
#include "statbag.hh"

StatBag S;

extern "C" void setEDNSOption(DNSQuestion *q, uint16_t code, std::string *opt);

class FuzzedDataProvider {
public:
  FuzzedDataProvider(const uint8_t *data, size_t size)
      : data_(data), size_(size), pos_(0) {}

  template <typename T>
  T ConsumeIntegralInRange(T min, T max) {
    if (pos_ + sizeof(T) > size_) {
      return min;
    }
    T value;
    memcpy(&value, data_ + pos_, sizeof(T));
    pos_ += sizeof(T);
    return value;
  }

  std::string ConsumeBytes(size_t size) {
    if (pos_ + size > size_) {
      size = size_ - pos_;
    }
    std::string value(data_ + pos_, size);
    pos_ += size;
    return value;
  }

  size_t remaining_bytes() const { return size_ - pos_; }

private:
  const uint8_t *data_;
  size_t size_;
  size_t pos_;
};

// Define the setEDNSOption function
extern "C" void setEDNSOption(DNSQuestion *q, uint16_t code, std::string *opt) {
  // Implement the logic for setting the EDNS option
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
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

  // Call the setEDNSOption function to set the EDNS option
  setEDNSOption(&q, code, &opt);

  return 0;
}