#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "tiny_gltf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  tinygltf::TinyGLTF loader;
  tinygltf::Model model;
  std::string err;
  std::string warn;

  int length = stream.remaining_bytes();
  std::string base_dir = stream.ConsumeRandomLengthString();
  int base_dir_length = base_dir.length();

  std::vector<char> binary_data = stream.ConsumeRemainingBytes<char>();

  loader.LoadBinaryFromMemory(&model, &err, &warn, binary_data.data(), length, &base_dir, base_dir_length);

  return 0;
}