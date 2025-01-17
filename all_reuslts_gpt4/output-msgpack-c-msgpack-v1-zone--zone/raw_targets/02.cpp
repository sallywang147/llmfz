#include <msgpack.hpp>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize a zone with a random size
  size_t zoneSize = stream.ConsumeIntegral<size_t>();
  msgpack::v1::zone zone(zoneSize);

  // Consume some data from the zone
  while (stream.remaining_bytes() > 0) {
    size_t dataSize = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
    auto data = stream.ConsumeBytes<unsigned char>(dataSize);
    zone.allocate_align(dataSize, 1);
  }

  // Explicitly call the destructor
  zone.~zone();

  return 0;
}