#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "sx_pool.h"
#include "sx_context.h"

extern "C" {
#include "fx_context.h"
}

// Declare the function `fxRunContext` in the header `fx_context.h`.
extern "C" void fxRunContext(struct sxPool* pool, struct sxContext* context);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a pool of memory to use for allocations.
  struct sxPool* pool = sxPoolCreate(stream.ConsumeIntegral<uint32_t>());
  if (pool == nullptr) {
    return 0;
  }

  // Create a context to use for the fuzzed data.
  struct sxContext* context = sxContextCreate(pool);
  if (context == nullptr) {
    sxPoolDestroy(pool);
    return 0;
  }

  // Consume the fuzzed data and write it to the context.
  std::vector<uint8_t> fuzzed_data = stream.ConsumeRemainingBytes();
  sxContextWrite(context, fuzzed_data.data(), fuzzed_data.size());

  // Run the context.
  fxRunContext(pool, context);

  // Clean up.
  sxContextDestroy(context);
  sxPoolDestroy(pool);

  return 0;
}