#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc

extern "C" {
#include "tiny_obj_loader.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn;
  std::string err;
  if (Size < 2) {
    return 0;
  }
  for (size_t i = 0; i < Size - 1; i++) {
    if (Data[i] == 0) {
      std::string obj_text(reinterpret_cast<const char *>(Data), i);
      std::string mtl_text(reinterpret_cast<const char *>(Data + i + 1), Size - i - 1);
      tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err,
                       reinterpret_cast<char *>(obj_text.c_str()),
                       reinterpret_cast<char *>(mtl_text.c_str()), false, false);
      return 0;
    }
  }
  return 0;
}