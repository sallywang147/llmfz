#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "bt3zip.h"

extern "C" {  // Wrap the header with `extern "C" {}` to resolve the linking error.
#include "bt3zip_match_finder.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const uint32_t window_size = stream.ConsumeIntegral<uint32_t>();
  const uint32_t num_distances = stream.ConsumeIntegral<uint32_t>();
  struct _CMatchFinder match_finder;
  match_finder.NumDistances = num_distances;
  match_finder.Window = new uint8_t[window_size];
  match_finder.WindowTop = match_finder.Window;
  match_finder.WindowSize = window_size;

  const size_t input_size = stream.ConsumeIntegralInRange<size_t>(
      0, std::min(size, static_cast<size_t>(window_size)));
  std::vector<uint8_t> input_data = stream.ConsumeBytes<uint8_t>(input_size);
  memcpy(match_finder.WindowTop, input_data.data(), input_data.size());
  match_finder.WindowTop += input_data.size();

  int distances[num_distances];
  const int result =
      Bt3Zip_MatchFinder_GetMatches(&match_finder, distances);
  (void)result;

  delete[] match_finder.Window;
  return 0;
}