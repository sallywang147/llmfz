#include <fuzzer/FuzzedDataProvider.h>
#include <cstring>

extern "C" {
#include "libraw/libraw.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  LibRaw raw;
  raw.open_buffer(data, size);

  // Extract an array of bytes as a vector. You MUST call `.data()` to use result as pointer.
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size));
  const char *data_ptr = reinterpret_cast<const char *>(bytes.data());

  // Call the function to fuzz
  raw.unpack_function_name(data_ptr);

  return 0;
}