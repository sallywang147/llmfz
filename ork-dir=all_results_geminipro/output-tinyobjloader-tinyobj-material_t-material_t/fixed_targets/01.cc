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
  tinyobj::material_t material;
  tinyobj::material_t *material_ptr = &material;
  tinyobj::material_t material2;
  tinyobj::material_t *material2_ptr = &material2;
  *material_ptr = material;
  *material2_ptr = material2;
  return 0;
}