#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_IMPLEMENTATION
#include "tiny_gltf.h"
#include <fuzzer/FuzzedDataProvider.h>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  if (size < 1) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  tinygltf::Model model;
  tinygltf::TinyGLTF gltf_ctx;
  std::string err;
  std::string warn;

  const char *str = reinterpret_cast<const char *>(data);
  bool ret = gltf_ctx.LoadASCIIFromString(&model, &err, &warn, str, size, /* base_dir */ "");
  if (!ret) {
    return 0;
  }

  std::ostringstream oss;
  bool embedImages = stream.ConsumeBool();
  bool embedBuffers = stream.ConsumeBool();

  gltf_ctx.WriteGltfSceneToStream(&model, &oss, embedImages, embedBuffers);

  return 0;
}