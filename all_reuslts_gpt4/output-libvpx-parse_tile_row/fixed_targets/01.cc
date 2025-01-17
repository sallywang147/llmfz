#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

#include "vpx/vp8dx.h"
#include "vpx/vpx_decoder.h"
#include "vpx_ports/mem_ops.h"
#include "vp9/decoder/vp9_decoder.h"
#include "vp9/decoder/vp9_read_bit_buffer.h"
#include "vp9/decoder/vp9_reader.h"
#include "fuzzer/FuzzedDataProvider.h"

#define VPXD_INTERFACE(name) VPXD_INTERFACE_(name)
#define VPXD_INTERFACE_(name) vpx_codec_##name##_dx()

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 4) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  vpx_codec_ctx_t codec;
  vpx_codec_dec_cfg_t cfg = {0, 0, 0};
  if (vpx_codec_dec_init(&codec, VPXD_INTERFACE(DECODER), &cfg, 0)) {
    return 0;
  }

  // Initialize VP9Decoder and TileWorkerData objects
  VP9Decoder *pbi = new VP9Decoder();
  TileWorkerData *tile_data = new TileWorkerData();

  // Consume data for the row and column
  int row = stream.ConsumeIntegral<int>();
  int col = stream.ConsumeIntegral<int>();

  // Consume remaining data for the array of strings
  std::vector<std::string> str_vector;
  while (stream.remaining_bytes() > 0) {
    str_vector.push_back(stream.ConsumeRandomLengthString());
  }
  
  // Convert vector of strings to array of char pointers
  std::vector<char*> cstr_vector;
  for (auto &str : str_vector) {
    cstr_vector.push_back(const_cast<char*>(str.c_str()));
  }
  char **cstr_array = cstr_vector.data();

  // Call the target function
  parse_tile_row(tile_data, pbi, row, col, cstr_array);

  // Cleanup
  delete pbi;
  delete tile_data;
  vpx_codec_destroy(&codec);

  return 0;
}