#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "bt3zip.h"

extern "C" {
#include "lzma/LzmaLib.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct _CMatchFinder match_finder;
  match_finder.bt_tree = nullptr;
  match_finder.bt_tree_size = 0;
  match_finder.bt_tree_size_limit = 0;
  match_finder.bt_tree_size_limit_init = 0;
  match_finder.bt_tree_size_limit_max = 0;
  match_finder.bt_tree_size_limit_min = 0;
  match_finder.bt_tree_size_limit_step = 0;
  match_finder.bt_tree_size_limit_step_max = 0;
  match_finder.bt_tree_size_limit_step_min = 0;

  int distances[16];

  // Declare the function `Bt3Zip_MatchFinder_GetMatches`
  int Bt3Zip_MatchFinder_GetMatches(_CMatchFinder* match_finder, int* distances);

  // Call the function `Bt3Zip_MatchFinder_GetMatches`
  Bt3Zip_MatchFinder_GetMatches(&match_finder, distances);

  return 0;
}