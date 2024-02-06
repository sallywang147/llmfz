#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "tiny_obj_loader.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);

  tinyobj::ObjReader reader;
  tinyobj::ObjReaderConfig config;

  // Consume data for config
  config.triangulate = fuzzed_data.ConsumeBool();
  config.vertex_color = fuzzed_data.ConsumeBool();

  // Consume remaining data for filename
  std::string filename = fuzzed_data.ConsumeRemainingBytesAsString();

  // Call the function to fuzz
  reader.ParseFromFile(&filename, &config);

  return 0;
}