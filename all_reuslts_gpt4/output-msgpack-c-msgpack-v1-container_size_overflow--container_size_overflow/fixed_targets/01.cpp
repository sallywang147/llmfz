#include <fuzzer/FuzzedDataProvider.h>
#include <msgpack.hpp>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string errorMsg = stream.ConsumeRandomLengthString();
  try {
    throw msgpack::v1::container_size_overflow(errorMsg);
  } catch (msgpack::v1::container_size_overflow& e) {
    e.~container_size_overflow();
  }

  return 0;
}