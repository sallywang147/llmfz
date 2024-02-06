#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  tinyobj::ObjReaderConfig reader_config;
  tinyobj::ObjReader reader;
  std::string filename(reinterpret_cast<const char *>(Data), Size);
  reader.ParseFromFile(filename, reader_config);
  return 0;
}