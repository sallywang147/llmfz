#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "vp9/common/vp9_thread.h"
#include "vp9/decoder/vp9_decoder.h"
#include "vp9/decoder/vp9_read_bit_buffer.h"

#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Define and initialize the parameters for parse_tile_row
  struct TileWorkerData tile_worker_data;
  struct VP9Decoder vp9_decoder;
  int tile_row = stream.ConsumeIntegral<int>();
  int tile_col = stream.ConsumeIntegral<int>();

  // Create a char** from the remaining bytes
  std::vector<uint8_t> remaining_bytes = stream.ConsumeRemainingBytes<uint8_t>();
  char *remaining_bytes_char = reinterpret_cast<char*>(remaining_bytes.data());
  char *remaining_bytes_array[1] = {remaining_bytes_char};
  char **data_end = remaining_bytes_array;

  // Call the function to fuzz
  parse_tile_row(&tile_worker_data, &vp9_decoder, tile_row, tile_col, data_end);

  return 0;
}