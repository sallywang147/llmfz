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

extern "C" int LLVMFuzzerTestOneInput(std::uint8_t const *data, std::size_t size) {
  FuzzedDataProvider provider(data, size);

  tinygltf::TinyGLTF gltfContext;
  tinygltf::Model model;
  std::string outputFilename = "fuzz_output.gltf";
  
  bool embedImages = provider.ConsumeBool();
  bool embedBuffers = provider.ConsumeBool();
  bool prettyPrint = provider.ConsumeBool();
  bool writeBinary = provider.ConsumeBool();

  bool ret = gltfContext.WriteGltfSceneToFile(&model, &outputFilename, embedImages, embedBuffers, prettyPrint, writeBinary);

  return 0;
}