#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "archive.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  std::vector<uint8_t> bytes(data, data + size);
  Archive archive;
  archive.Read(bytes.data(), bytes.size());
  archive.SearchRR();

  return 0;
}