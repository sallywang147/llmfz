#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "Bt3Zip_MatchFinder.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the match finder
  struct _CMatchFinder matchFinder;
  Bt3Zip_MatchFinder_Construct(&matchFinder);

  // Allocate memory for distances
  int* distances = (int*)malloc(size * sizeof(int));
  if (distances == nullptr) {
    return 0;
  }

  // Feed data to match finder
  if (stream.remaining_bytes() > 0) {
    const size_t next_size = stream.ConsumeIntegralInRange<size_t>(0, stream.remaining_bytes());
    auto next_input = stream.ConsumeBytes<unsigned char>(next_size);
    Bt3Zip_MatchFinder_SetPointerToCurrentPos(&matchFinder, next_input.data());
  }

  // Call the function to fuzz
  Bt3Zip_MatchFinder_GetMatches(&matchFinder, distances);

  // Cleanup
  free(distances);

  return 0;
}