#include <stdint.h>
#include <stddef.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "Builtin_tests_importer.h"
}

void LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider fuzzed_data(data, size);
  union anon input;
  input.bytes = fuzzed_data.ConsumeBytes<uint8_t>(sizeof(input.bytes));
  cryptofuzz::Builtin_tests_importer::Run(&input);
}