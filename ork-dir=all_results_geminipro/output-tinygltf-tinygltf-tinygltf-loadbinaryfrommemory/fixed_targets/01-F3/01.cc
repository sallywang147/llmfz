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
#include "stb_image.h"
#include "stb_image_write.h"
}

static void parse_intCoding4(const uint8_t *data, size_t size) {

  tinygltf::TinyGLTF ctx;
  tinygltf::Model model;
  std::string err;
  std::string warn;

  const char *str = reinterpret_cast<const char *>(data);

  bool ret = ctx.LoadBinaryFromMemory(&ctx, &model, &err, &warn, str, size,
                                     /* base_dir */ "", /* check_redundant_materials */ 0);
  (void)ret;
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  parse_intCoding4(data, size);
  return 0;
}