#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include "fxlib.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct sxPool* pool = nullptr;
  struct sxContext* context = nullptr;
  const std::string path = stream.ConsumeRemainingBytesAsString();
  const int flags = stream.ConsumeIntegral<int>();
  const int async = stream.ConsumeIntegral<int>();
  const std::string message = stream.ConsumeRemainingBytesAsString();

  int result = fxRunTestCase(pool, context, path.data(),
                            flags, async, message.data());
  return result;
}