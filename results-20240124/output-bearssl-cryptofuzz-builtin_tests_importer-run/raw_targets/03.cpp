 #include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "cryptofuzz/Builtin_tests_importer.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  static bool initialized = false;
  if (!initialized) {
    cryptofuzz::Builtin_tests_importer::Initialize();
    initialized = true;
  }

  std::vector<uint8_t> input_buffer(data, data + size);
  cryptofuzz::Builtin_tests_importer::Run((union.anon*)input_buffer.data());
  return 0;
}