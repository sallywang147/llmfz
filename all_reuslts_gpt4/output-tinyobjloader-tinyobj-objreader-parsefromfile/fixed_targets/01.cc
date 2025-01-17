#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tiny_obj_loader.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize ObjReader and ObjReaderConfig
  tinyobj::ObjReader reader;
  tinyobj::ObjReaderConfig config;

  // Extract a string to use as the filename. The filename doesn't actually matter for fuzzing.
  std::string filename = stream.ConsumeRandomLengthString();

  // Set the config parameters using the fuzzed data
  config.triangulate = stream.ConsumeBool();
  config.vertex_color = stream.ConsumeBool();

  // Call the function to fuzz
  reader.ParseFromFile(&filename, &config);

  return 0;
}