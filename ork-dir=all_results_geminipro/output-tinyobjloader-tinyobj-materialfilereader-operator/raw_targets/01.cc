#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  tinyobj::MaterialFileReader reader;
  std::string matId;
  std::vector<tinyobj::material_t> materials;
  std::map<std::string, tinyobj::material_t> matMap;
  std::string warn;
  std::string err;
  reader.operator()(&matId, &materials, &matMap, &warn, &err);
  return 0;
}