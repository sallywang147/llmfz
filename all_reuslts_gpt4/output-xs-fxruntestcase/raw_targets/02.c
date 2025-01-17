#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "fx.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct sxPool pool;
  struct sxContext context;

  // Initialize the pool and context
  sxPoolInit(&pool);
  sxContextInit(&context, &pool);

  // Generate the path, flags, async and message from the data stream
  std::string path = stream.ConsumeRandomLengthString().c_str();
  int flags = stream.ConsumeIntegral<int>();
  int async = stream.ConsumeBool();
  std::string message = stream.ConsumeRandomLengthString().c_str();

  // Call the target function
  fxRunTestCase(&pool, &context, path, flags, async, message);

  // Cleanup
  sxContextFree(&context);
  sxPoolFree(&pool);

  return 0;
}