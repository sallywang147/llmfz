#include <fuzzer/FuzzedDataProvider.h>
#include <cstdio>
#include <cstdlib>
#include <string>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string filename = stream.ConsumeRandomLengthString();
  filename = "/tmp/" + filename;
  FILE* file = fopen(filename.c_str(), "wb");
  if (!file) {
    return 0;
  }

  std::vector<uint8_t> buffer = stream.ConsumeRemainingBytes<uint8_t>();
  fwrite(buffer.data(), 1, buffer.size(), file);
  fclose(file);

  int x, y, comp;
  stbi_info((char*)filename.c_str(), &x, &y, &comp);

  remove(filename.c_str());

  return 0;
}