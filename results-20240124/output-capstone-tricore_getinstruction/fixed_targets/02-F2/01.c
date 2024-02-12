#include <fuzzer/FuzzedDataProvider.h>

#include <algorithm>
#include <cstdint>
#include <cstring>
#include <cstdlib>
#include <cstdio>

extern "C" {
#include "TriCoreDisassembler.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t handle = stream.ConsumeIntegral<size_t>();
  const size_t byte_len = stream.ConsumeIntegral<size_t>();
  const size_t address = stream.ConsumeIntegral<size_t>();
  char *bytes = new char[byte_len];
  stream.ConsumeBytes<char>(bytes, byte_len);
  struct MCInst *mi = new struct MCInst();
  short *size = new short();
  char *info = new char[100];
  bool result = TriCore_getInstruction(handle, bytes, byte_len, mi, size, address, info);
  delete[] bytes;
  delete mi;
  delete size;
  delete[] info;
  return 0;
}