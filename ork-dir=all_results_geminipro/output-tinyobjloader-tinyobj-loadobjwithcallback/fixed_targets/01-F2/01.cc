#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <string>
#include <sstream>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"

extern "C" {
#include "tiny_obj_loader.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  std::string obj_text(reinterpret_cast<const char *>(Data), Size);
  std::istringstream obj_stream(obj_text);
  tinyobj::callback_t cb;
  tinyobj::LoadObjWithCallback(&obj_stream, &cb, nullptr, nullptr, nullptr, nullptr);
  return 0;
}