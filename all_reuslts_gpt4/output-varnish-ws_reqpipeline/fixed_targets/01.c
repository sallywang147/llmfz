#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "ws.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a ws struct
  struct ws ws;
  
  // Consume data to create two strings for b and e
  std::string b = stream.ConsumeBytesAsString(stream.remaining_bytes() / 2);
  std::string e = stream.ConsumeRemainingBytesAsString();

  // Call the target function
  int result = WS_ReqPipeline(&ws, const_cast<char *>(b.c_str()), const_cast<char *>(e.c_str()));

  return 0;
}