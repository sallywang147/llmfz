#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "unbound.h"

// Define a callback function
void callback(void *mydata, int err, struct ub_result* result) {
  // We don't need to do anything in the callback for fuzzing
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the context
  struct ub_ctx* ctx;
  ctx = ub_ctx_create();
  if (!ctx) {
    return 0;
  }

  // Consume data for the name parameter
  std::string name = stream.ConsumeRandomLengthString();
  if (name.empty()) {
    ub_ctx_delete(ctx);
    return 0;
  }

  // Consume data for the rrtype and rrclass parameters
  int rrtype = stream.ConsumeIntegral<int>();
  int rrclass = stream.ConsumeIntegral<int>();

  // Consume data for the mydata parameter
  std::string mydata = stream.ConsumeRandomLengthString();

  // Initialize the async_id parameter
  int async_id;

  // Call the function to fuzz
  ub_resolve_event(ctx, const_cast<char*>(name.c_str()), rrtype, rrclass, const_cast<char*>(mydata.c_str()), callback, &async_id);

  // Clean up
  ub_ctx_delete(ctx);

  return 0;
}