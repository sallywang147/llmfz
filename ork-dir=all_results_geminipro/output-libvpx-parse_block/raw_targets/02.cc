#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

extern "C" void parse_block(struct TileWorkerData*, struct VP9Decoder*, int, int, char, int, int);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  struct TileWorkerData* tile_worker_data = new TileWorkerData;
  struct VP9Decoder* vp9_decoder = new VP9Decoder;
  FuzzedDataProvider provider(data, size);
  int arg_1 = provider.ConsumeIntegralInRange<int>(0, 100);
  int arg_2 = provider.ConsumeIntegralInRange<int>(0, 100);
  char arg_3 = provider.ConsumeIntegral<char>();
  int arg_4 = provider.ConsumeIntegralInRange<int>(0, 100);
  int arg_5 = provider.ConsumeIntegralInRange<int>(0, 100);
  parse_block(tile_worker_data, vp9_decoder, arg_1, arg_2, arg_3, arg_4, arg_5);
  delete tile_worker_data;
  delete vp9_decoder;
  return 0;
}