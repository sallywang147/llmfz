#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "EncoderCore.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  
  EncoderCore<short, true> *encoder = new EncoderCore<short, true>();
  if (!encoder) {
    return 0;
  }

  size_t bufferSize = provider.ConsumeIntegralInRange<size_t>(0, 1024);
  char *buffer = new char[bufferSize];
  if (!buffer) {
    delete encoder;
    return 0;
  }

  bool flag = provider.ConsumeBool();

  encoder->Run(encoder, buffer, bufferSize, flag);

  delete[] buffer;
  delete encoder;

  return 0;
}