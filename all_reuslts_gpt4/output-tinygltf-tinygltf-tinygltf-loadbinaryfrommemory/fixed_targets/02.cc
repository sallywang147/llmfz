#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <string>

#include "tiny_gltf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  tinygltf::TinyGLTF loader;
  tinygltf::Model model;
  std::string err;
  std::string warn;

  std::string base_dir = stream.ConsumeRandomLengthString();
  char* bin_data = const_cast<char*>(reinterpret_cast<const char*>(stream.ConsumeRemainingBytes().data()));
  int bin_size = static_cast<int>(stream.remaining_bytes());

  std::string bin_filename = stream.ConsumeRandomLengthString();
  int check_sections = stream.ConsumeIntegral<int>();

  loader.LoadBinaryFromMemory(&model, &err, &warn, bin_data, bin_size, &base_dir, &bin_filename, check_sections);

  return 0;
}