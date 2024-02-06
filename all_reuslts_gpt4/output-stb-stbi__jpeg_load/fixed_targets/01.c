#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "stb_image.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  int x = 0;
  int y = 0;
  int comp = 0;
  int req_comp = stream.ConsumeIntegralInRange<int>(0, 4);
  stbi__result_info ri;

  stbi__context s;
  stbi__start_mem(&s, data, size);

  char* result = stbi__jpeg_load(&s, &x, &y, &comp, req_comp, &ri);

  stbi_image_free(result);

  return 0;
}