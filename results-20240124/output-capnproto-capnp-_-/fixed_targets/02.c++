#include <stddef.h>
#include <stdint.h>
#include <fuzzer/FuzzedDataProvider.h>

extern "C" {
#include "llvm/Fuzz/libfuzzer/libfuzzer_exports.h"
}

// This function will be called by the fuzzer.
// It takes a pointer to a buffer and its size as input.
int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  // Do something with the data here.
  return 0;
}