#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "stb_image.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);

  int x, y, comp;
  struct stbi__jpeg jpeg;
  stbi__start_mem(&jpeg.s, data, size);

  int req_comp = provider.ConsumeIntegralInRange<int>(0, 4);

  char* img = load_jpeg_image(&jpeg, &x, &y, &comp, req_comp);

  if (img != NULL) {
    free(img);
  }

  return 0;
}