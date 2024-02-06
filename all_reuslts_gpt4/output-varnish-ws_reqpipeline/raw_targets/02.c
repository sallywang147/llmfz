#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ws.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct ws *ws = WS_Alloc(1); // Assuming WS_Alloc is a function that allocates a ws structure.

  if(ws == nullptr) {
    return 0;
  }

  // Split the input into two parts to use as 'b' and 'e'.
  size_t split_point = stream.ConsumeIntegralInRange<size_t>(0, size);
  std::string str1 = stream.ConsumeBytesAsString(split_point);
  std::string str2 = stream.ConsumeRemainingBytesAsString();

  // Call the function under test.
  int result = WS_ReqPipeline(ws, str1.data(), str2.data());

  // Clean up.
  WS_Free(ws); // Assuming WS_Free is a function that frees a ws structure.

  return 0;
}