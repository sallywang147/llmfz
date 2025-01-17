#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "stb_image.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize the jpeg structure
  stbi__jpeg jpeg;
  jpeg.s = NULL;
  jpeg.img_comp = NULL;
  jpeg.progressive = stream.ConsumeBool();

  // Initialize the output parameters
  int out_x = stream.ConsumeIntegral<int>();
  int out_y = stream.ConsumeIntegral<int>();
  int comp = stream.ConsumeIntegral<int>();
  int req_comp = stream.ConsumeIntegral<int>();

  // Call the function to fuzz
  char* result = load_jpeg_image(&jpeg, &out_x, &out_y, &comp, req_comp);

  // Free the result
  free(result);

  return 0;
}