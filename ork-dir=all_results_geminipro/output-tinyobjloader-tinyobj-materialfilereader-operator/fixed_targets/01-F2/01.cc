#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"

extern "C" {
#include "tiny_obj_loader_c_wrapper.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  tinyobj_material_reader_t reader;
  tinyobj_material_reader_init(&reader);

  std::string matId;
  std::vector<tinyobj::material_t> materials;
  std::map<std::string, tinyobj::material_t> matMap;
  std::string warn;
  std::string err;

  bool success = tinyobj_material_reader_read_string(&reader, reinterpret_cast<const char *>(Data), Size, &matId, &materials, &matMap, &warn, &err);
  if (!success) {
    return 0;
  }
  return 0;
}