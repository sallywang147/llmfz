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

void parse_intCoding4(const uint8_t *data, size_t size) {

  tinygltf::TinyGLTF ctx;
  tinygltf::Model model;
  std::string err;
  std::string warn;

  bool ret = ctx.LoadBinaryFromMemory(&model, &err, &warn,
                                      reinterpret_cast<char *>(const_cast<uint8_t *>(data)),
                                      size, /* base_dir */ "");
  (void)ret;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  parse_intCoding4(data, size);
  return 0;
}