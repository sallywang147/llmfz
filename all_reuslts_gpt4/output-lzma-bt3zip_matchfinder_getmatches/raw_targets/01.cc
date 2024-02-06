#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "Bt3Zip_MatchFinder.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  // Initialize the _CMatchFinder struct
  struct _CMatchFinder matchFinder;
  Bt3Zip_MatchFinder_Construct(&matchFinder);

  // Allocate memory for the struct's buffer and fill it with fuzzed data
  size_t buffer_size = stream.ConsumeIntegralInRange<size_t>(1, size);
  matchFinder.buffer = (Byte *)malloc(buffer_size);
  std::vector<uint8_t> buffer_data = stream.ConsumeBytes<uint8_t>(buffer_size);
  memcpy(matchFinder.buffer, buffer_data.data(), buffer_size);

  // Initialize other parameters of the struct
  matchFinder.pos = stream.ConsumeIntegral<UInt32>();
  matchFinder.bufferBase = matchFinder.buffer - matchFinder.pos;
  matchFinder.streamPos = stream.ConsumeIntegral<UInt32>();
  matchFinder.lenLimit = stream.ConsumeIntegral<UInt32>();
  matchFinder.cyclicBufferPos = stream.ConsumeIntegral<UInt32>();
  matchFinder.cyclicBufferSize = stream.ConsumeIntegral<UInt32>();
  matchFinder.hash = (UInt32 *)malloc(matchFinder.cyclicBufferSize * sizeof(UInt32));
  matchFinder.son = (UInt32 *)malloc((matchFinder.cyclicBufferSize * 2) * sizeof(UInt32));

  // Initialize distances array
  int distances[buffer_size];
  
  // Call the target function
  Bt3Zip_MatchFinder_GetMatches(&matchFinder, distances);

  // Free allocated memory
  free(matchFinder.buffer);
  free(matchFinder.hash);
  free(matchFinder.son);

  return 0;
}