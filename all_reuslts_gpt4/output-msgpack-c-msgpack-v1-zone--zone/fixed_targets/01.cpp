#include <fuzzer/FuzzedDataProvider.h>
#include <msgpack.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a zone object
  msgpack::v1::zone z;

  // We need to consume some data to make the fuzzing meaningful
  while (stream.remaining_bytes() > 0) {
    size_t chunk_size = stream.ConsumeIntegralInRange<size_t>(1, stream.remaining_bytes());
    auto chunk_data = stream.ConsumeBytes<uint8_t>(chunk_size);

    // Use the data somehow with the zone object
    // Here we just create a raw object and push it into the zone
    msgpack::v1::object obj(msgpack::v1::type::RAW, chunk_data.data(), chunk_size);
    z.push_finalizer(&msgpack::v1::object::decref, &obj);
  }

  // Call the destructor
  z.~zone();

  return 0;
}