#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include "TriCore.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t handle = stream.ConsumeIntegral<size_t>();
  const std::string bytes_string = stream.ConsumeRemainingBytesAsString();
  char* bytes = const_cast<char*>(bytes_string.c_str());
  const size_t byte_len = stream.ConsumeIntegral<size_t>();
  struct MCInst* mi = new struct MCInst;
  short* size = new short;
  const size_t address = stream.ConsumeIntegral<size_t>();
  const std::string info_string = stream.ConsumeRemainingBytesAsString();
  char* info = const_cast<char*>(info_string.c_str());
  TriCore_getInstruction(handle, bytes, byte_len, mi, size, address, info);
  delete mi;
  delete size;
  return 0;
}