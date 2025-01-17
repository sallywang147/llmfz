#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "flatbuffers/flatbuffers.h"
}

void LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  flatbuffers::Parser parser;
  parser.Parse(fuzzed_data.ConsumeRemainingBytes<const char *>());
  parser.Serialize();
}