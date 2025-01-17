#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "brunsli/decode.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a BrunsliDecoder object
  brunsli::BrunsliDecoder decoder;

  // Initialize the input and output pointers
  size_t available_in = stream.remaining_bytes();
  const uint8_t* next_in = stream.data();
  size_t available_out = 0;
  uint8_t* next_out = nullptr;

  // Call the Decode function
  brunsli::BrunsliDecoder::Status status = decoder.Decode(&available_in, &next_in, &available_out, &next_out);

  return 0;
}