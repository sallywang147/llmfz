#include "libraw/libraw.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  LibRaw raw;
  raw.open_buffer(data, size);

  // Extract an array of bytes as a vector. You MUST call `.data()` to use result as pointer.
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(stream.ConsumeIntegralInRange(0, size));
  void *data_ptr = bytes.data();

  // Call the function to fuzz
  raw.unpack_function_name((LibRaw *)data_ptr);

  return 0;
}