#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ole2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider provider(data, size);
  std::vector<uint8_t> bytes = provider.ConsumeRemainingBytes();
  std::string str(bytes.begin(), bytes.end());
  char* file = const_cast<char*>(str.c_str());

  struct OLE2 *ole = ole2_open_file(file);
  if (ole) {
    ole2_close(ole);
  }
  return 0;
}