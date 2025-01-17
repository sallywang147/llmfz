#include <fuzzer/FuzzedDataProvider.h>

#include <cstdint>
#include <string>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_IMPLEMENTATION
#include "tiny_gltf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  if (size == 0) {
    return 0;
  }

  FuzzedDataProvider stream(data, size);

  tinygltf::TinyGLTF gltfContext;
  tinygltf::Model model;
  std::string err;
  std::string warn;

  const char *str = reinterpret_cast<const char *>(data);
  bool ret = gltfContext.LoadASCIIFromString(&model, &err, &warn, str, size, /* base_dir */ "");
  if (!ret) {
    return 0;
  }

  std::string output_filename = "/dev/null";
  bool embedImages = stream.ConsumeBool();
  bool embedBuffers = stream.ConsumeBool();
  bool prettyPrint = stream.ConsumeBool();
  bool writeBinary = stream.ConsumeBool();

  gltfContext.WriteGltfSceneToFile(&model, output_filename, embedImages, embedBuffers, prettyPrint, writeBinary);

  return 0;
}