#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "fx.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  const size_t pool_size = provider.ConsumeIntegralInRange<size_t>(
      0, 1 << 20);
  struct sxPool* pool = sxPoolCreate(pool_size);
  if (pool == nullptr) {
    return 0;
  }

  const size_t context_size = provider.ConsumeIntegralInRange<size_t>(
      0, 1 << 20);
  struct sxContext* context = sxContextCreate(pool, context_size);
  if (context == nullptr) {
    sxPoolDestroy(pool);
    return 0;
  }

  fxRunContext(pool, context);

  sxContextDestroy(context);
  sxPoolDestroy(pool);

  return 0;
}