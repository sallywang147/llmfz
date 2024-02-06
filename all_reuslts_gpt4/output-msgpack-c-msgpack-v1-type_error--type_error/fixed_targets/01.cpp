#include <msgpack.hpp>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a type_error object
  msgpack::v1::type_error type_error_obj;

  // The destructor for type_error will be called automatically when the function scope ends.

  return 0;
}