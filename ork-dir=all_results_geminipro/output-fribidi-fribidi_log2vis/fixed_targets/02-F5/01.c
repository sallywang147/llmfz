#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "fribidi.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const uint8_t str_size = stream.ConsumeIntegral<uint8_t>();
  const uint8_t base_dir = stream.ConsumeIntegral<uint8_t>();
  const uint8_t visual_str_size = stream.ConsumeIntegral<uint8_t>();
  const uint8_t positions_L_to_V_size = stream.ConsumeIntegral<uint8_t>();
  const uint8_t positions_V_to_L_size = stream.ConsumeIntegral<uint8_t>();
  const uint8_t embedding_levels_size = stream.ConsumeIntegral<uint8_t>();

  int* str = new int[str_size];
  int* pbase_dir = new int[1];
  int* visual_str = new int[visual_str_size];
  int* positions_L_to_V = new int[positions_L_to_V_size];
  int* positions_V_to_L = new int[positions_V_to_L_size];
  char* embedding_levels = new char[embedding_levels_size];

  for (size_t i = 0; i < str_size; i++) {
    str[i] = stream.ConsumeIntegral<int>();
  }
  *pbase_dir = base_dir;
  for (size_t i = 0; i < visual_str_size; i++) {
    visual_str[i] = stream.ConsumeIntegral<int>();
  }
  for (size_t i = 0; i < positions_L_to_V_size; i++) {
    positions_L_to_V[i] = stream.ConsumeIntegral<int>();
  }
  for (size_t i = 0; i < positions_V_to_L_size; i++) {
    positions_V_to_L[i] = stream.ConsumeIntegral<int>();
  }
  for (size_t i = 0; i < embedding_levels_size; i++) {
    embedding_levels[i] = stream.ConsumeIntegral<char>();
  }

  fribidi_log2vis(str, str_size, pbase_dir, visual_str, positions_L_to_V,
                  positions_V_to_L, embedding_levels);

  delete[] str;
  delete[] pbase_dir;
  delete[] visual_str;
  delete[] positions_L_to_V;
  delete[] positions_V_to_L;
  delete[] embedding_levels;

  return 0;
}