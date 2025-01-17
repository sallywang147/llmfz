#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>
#include <fuzzer/FuzzedDataProvider.h>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_IMPLEMENTATION
#include "tiny_gltf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);
  std::string err;
  std::string warn;
  std::string filename = stream.ConsumeRandomLengthString();
  int defaultScene = stream.ConsumeIntegral<int>();

  tinygltf::TinyGLTF loader;
  tinygltf::Model model;

  bool ret = loader.LoadASCIIFromFile(&model, &err, &warn, filename, defaultScene);
  (void)ret;

  return 0;
}