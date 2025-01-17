#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "fribidi.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract flags
  int flags = stream.ConsumeIntegral<int>();

  // Extract len
  int len = stream.ConsumeIntegralInRange<int>(0, 100);

  // Extract embedding_levels
  std::string embedding_levels = stream.ConsumeBytesAsString(len);
  
  // Extract ar_props
  std::string ar_props = stream.ConsumeBytesAsString(len);

  // Extract str
  std::vector<int> str = stream.ConsumeIntegralInRange<int>(0, len);

  // Call the function
  fribidi_shape_arabic(flags, embedding_levels.data(), len, ar_props.data(), str.data());

  return 0;
}