#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "Zydis/Zydis.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume a string from the data provider
  std::string str = stream.ConsumeRandomLengthString();
  char* ptr = const_cast<char*>(str.c_str());

  // Call the function under test
  ZydisEncoderNopFill(ptr, str.size());

  return 0;
}