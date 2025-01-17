#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tiny_obj_loader.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn;
  std::string err;

  std::string filename = stream.ConsumeRandomLengthString().c_str();
  std::string mtl_basedir = stream.ConsumeRandomLengthString().c_str();
  bool triangulate = stream.ConsumeBool();
  bool default_vcols_fallback = stream.ConsumeBool();

  tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filename.c_str(), mtl_basedir.c_str(), triangulate, default_vcols_fallback);

  return 0;
}