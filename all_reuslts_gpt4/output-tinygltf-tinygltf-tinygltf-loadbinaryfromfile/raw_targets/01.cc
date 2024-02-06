#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_IMPLEMENTATION
#include "tiny_gltf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  tinygltf::TinyGLTF gltf_ctx;
  tinygltf::Model model;
  std::string err;
  std::string warn;

  // Write data to a temporary file
  std::ofstream tmp_file("tmp.gltf", std::ios::binary);
  tmp_file.write(reinterpret_cast<const char*>(data), size);
  tmp_file.close();

  // Load the binary file
  bool ret = gltf_ctx.LoadBinaryFromFile(&model, &err, &warn, "tmp.gltf");

  // Delete the temporary file
  std::remove("tmp.gltf");

  return 0;
}