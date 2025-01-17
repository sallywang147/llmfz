#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "sx.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the pool and context structures
  struct sxPool pool;
  struct sxContext context;

  // Consume data for pool and context
  if (stream.remaining_bytes() < sizeof(pool) + sizeof(context)) {
    return 0;
  }
  stream.ConsumeData(&pool, sizeof(pool));
  stream.ConsumeData(&context, sizeof(context));

  // Call the function to fuzz
  fxRunContext(&pool, &context);

  return 0;
}