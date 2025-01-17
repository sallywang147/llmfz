#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>
#include "tiny_obj_loader.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  tinyobj::attrib_t attrib;
  std::vector<tinyobj::shape_t> shapes;
  std::vector<tinyobj::material_t> materials;
  std::string warn;
  std::string err;

  // Consume data for filename and mtl_basedir
  std::string filename = fuzzed_data.ConsumeRandomLengthString();
  std::string mtl_basedir = fuzzed_data.ConsumeRandomLengthString();

  // Consume data for triangulate and default_vcols_fallback
  bool triangulate = fuzzed_data.ConsumeBool();
  bool default_vcols_fallback = fuzzed_data.ConsumeBool();

  // Call the function to fuzz
  tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, (char*)filename.c_str(), (char*)mtl_basedir.c_str(), triangulate, default_vcols_fallback);

  return 0;
}