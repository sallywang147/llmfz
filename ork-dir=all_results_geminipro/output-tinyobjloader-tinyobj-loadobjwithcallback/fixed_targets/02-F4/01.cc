#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TINYOBJLOADER_IMPLEMENTATION // define this in only *one* .cc
#include "tiny_obj_loader.h"

extern "C" {
#include "tiny_obj_loader.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  tinyobj::callback_t callback;
  callback.user_data = NULL;
  callback.callback_fn = NULL;
  std::string warn;
  std::string err;
  std::istringstream inStream(std::string(reinterpret_cast<const char *>(Data), Size));
  tinyobj::LoadObjWithCallback(&inStream, &callback, NULL, NULL, &warn, &err);
  return 0;
}