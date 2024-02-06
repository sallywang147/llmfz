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
  ::printf("success\n");
  return 0;
}