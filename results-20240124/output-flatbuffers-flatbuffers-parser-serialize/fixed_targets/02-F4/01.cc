#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "flatbuffers/flatbuffers.h"
}

void LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  flatbuffers::Parser parser;
  parser.Parse(fdp.ConsumeRemainingBytes<char>());
  parser.Serialize(nullptr);
}