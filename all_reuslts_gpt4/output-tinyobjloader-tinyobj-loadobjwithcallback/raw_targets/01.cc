#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <sstream>
#include <string>

#include "tiny_obj_loader.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  std::string input_data = stream.ConsumeRemainingBytesAsString();
  std::istringstream input_stream(input_data);

  tinyobj::callback_t callback;
  std::string warn;
  std::string err;

  tinyobj::LoadObjWithCallback(&input_stream, &callback, nullptr, nullptr, &warn, &err);

  return 0;
}