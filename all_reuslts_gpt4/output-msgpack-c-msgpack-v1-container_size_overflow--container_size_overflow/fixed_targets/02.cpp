#include <msgpack.hpp>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create an instance of std::length_error with a random string.
  std::string errorMessage = stream.ConsumeRandomLengthString();
  std::length_error lengthError(errorMessage);

  // Create an instance of msgpack::v1::container_size_overflow using the length error.
  msgpack::v1::container_size_overflow containerSizeOverflow(lengthError);

  // Explicitly call the destructor.
  containerSizeOverflow.~container_size_overflow();

  return 0;
}