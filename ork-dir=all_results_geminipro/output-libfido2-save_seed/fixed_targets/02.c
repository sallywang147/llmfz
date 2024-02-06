#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include <stdio.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const std::string opt = stream.ConsumeRemainingBytesAsString();
  save_seed(opt.c_str());
  return 0;
}

void save_seed(const char* seed) {
  // Save the seed to a file or database for later analysis.
  printf("Seed: %s\n", seed);
}