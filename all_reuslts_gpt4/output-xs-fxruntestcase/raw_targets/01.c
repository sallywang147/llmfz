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
  sxPoolInit(&pool, NULL, NULL);
  sxContextInit(&context, &pool);

  // Consume data to create the path
  std::string path = stream.ConsumeRandomLengthString();
  
  // Consume data to create the flags
  int flags = stream.ConsumeIntegral<int>();

  // Consume data to create the async
  int async = stream.ConsumeIntegral<int>();

  // Consume data to create the message
  std::string message = stream.ConsumeRandomLengthString();

  // Call the function
  fxRunTestCase(&pool, &context, const_cast<char*>(path.c_str()), flags, async, const_cast<char*>(message.c_str()));

  // Cleanup
  sxContextFree(&context);
  sxPoolFree(&pool);

  return 0;
}