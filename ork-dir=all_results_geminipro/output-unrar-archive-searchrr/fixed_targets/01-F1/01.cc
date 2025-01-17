#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "archive.h"

extern "C" {
#include "libfuzzer/libfuzzer_macro.h"
}

DEFINE_FUZZER(LLVMFuzzerTestOneInput) {
  std::vector<uint8_t> bytes(data, data + size);
  Archive archive;
  archive.Read(bytes.data(), bytes.size());
  archive.SearchRR();
}