#include <cstdint>
#include <cstring>
#include <iostream>
#include <memory>
#include <vector>

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define TINYGLTF_IMPLEMENTATION
#include "tiny_gltf.h"

extern "C" {
#include "tiny_gltf.h"
}

static void parse_binary(const uint8_t *data, size_t size) {

  tinygltf::Model model;
  tinygltf::TinyGLTF ctx;
  std::string err;
  std::string warn;

  const char *str = reinterpret_cast<const char *>(data);

  bool ret = ctx.LoadBinaryFromMemory(&model, &err, &warn, str, size, /* base_dir */ "");
  (void)ret;
}

extern "C" int LLVMFuzzerTestOneInput(std::uint8_t const *data, std::size_t size) {
  parse_binary(data, size);

  // Call the function that was not called by the fuzz target
  tinygltf::Model model;
  tinygltf::TinyGLTF ctx;
  std::string err;
  std::string warn;

  const char *str = reinterpret_cast<const char *>(data);

  bool ret = ctx.LoadBinaryFromFile(&model, &err, &warn, str, /* base_dir */ "");
  (void)ret;

  return 0;
}