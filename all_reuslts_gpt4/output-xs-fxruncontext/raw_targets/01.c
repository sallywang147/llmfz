#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "sx.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Initialize the pool and context
  struct sxPool pool;
  struct sxContext context;

  // Fill the pool and context with fuzzed data
  FuzzedDataProvider stream(data, size);
  
  // Consume data for pool and context
  size_t consumed = stream.ConsumeData(&pool, sizeof(pool));
  consumed += stream.ConsumeData(&context, sizeof(context));

  // If not enough data was consumed to fill both structures, return early
  if (consumed < sizeof(pool) + sizeof(context)) {
    return 0;
  }

  // Run the context with the fuzzed pool and context
  fxRunContext(&pool, &context);

  return 0;
}