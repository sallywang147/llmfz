#include <fuzzer/FuzzedDataProvider.h>
#include "lzo/lzo2a.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 2) {
    return 0;  // not enough data to do anything meaningful
  }
  
  FuzzedDataProvider stream(data, size);
  
  // The lzo2a_999_swd_t struct is typically initialized by calling
  // lzo2a_999_compress_dict_start, but since we're only testing
  // swd_insertdict, we'll just zero-initialize it.
  lzo2a_999_swd_t swd = {};

  // Consume data for node and len parameters
  size_t node = stream.ConsumeIntegral<size_t>();
  size_t len = stream.ConsumeIntegral<size_t>();

  // Call the function under test
  swd_insertdict(&swd, node, len);

  return 0;
}