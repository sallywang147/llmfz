#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "apr.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  apr_pool_t* pool = apr_pool_create_ex(nullptr, nullptr, nullptr);
  register_hooks(pool);
  apr_pool_destroy(pool);
  return 0;
}