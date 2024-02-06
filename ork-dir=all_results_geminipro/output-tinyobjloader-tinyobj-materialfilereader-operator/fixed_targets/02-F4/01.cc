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
  tinyobj::ObjReaderConfig readerConfig;
  tinyobj::ObjReader reader;

  std::string err = reader.ParseObj(&readerConfig, Data, Size);
  if (!err.empty()) {
    ::printf("failed\n");
    return 0;
  }

  std::string matId;
  std::vector<tinyobj::material_t> materials;
  std::map<std::string, int> matMap;
  std::string warn;
  std::string errMat;
  bool ret = reader.MaterialFileReader(matId, &materials, &matMap, &warn, &errMat);
  if (!ret) {
    ::printf("failed\n");
    return 0;
  }
  ::printf("success\n");
  return 0;
}