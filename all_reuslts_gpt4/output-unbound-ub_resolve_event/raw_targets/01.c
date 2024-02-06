#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "unbound.h"

// Define a callback function for the ub_resolve_event
void callback(void* mydata, int err, struct ub_result* result) {
  // We don't need to do anything here for fuzzing
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    ub_init();
    initialized = true;
  }
  int ret;
  struct ub_ctx* ctx = ub_ctx_create();
  if (ctx == nullptr) {
    return 0;
  }

  FuzzedDataProvider provider(data, size);

  // Consume data for parameters
  std::string name = provider.ConsumeRandomLengthString();
  int rrtype = provider.ConsumeIntegral<int>();
  int rrclass = provider.ConsumeIntegral<int>();
  std::string mydata = provider.ConsumeRandomLengthString();
  func_type* callback = &callback;
  int async_id = provider.ConsumeIntegral<int>();

  // Call the function to fuzz
  ret = ub_resolve_event(ctx, name.c_str(), rrtype, rrclass, mydata.c_str(), callback, &async_id);

  ub_ctx_delete(ctx);

  return 0;
}