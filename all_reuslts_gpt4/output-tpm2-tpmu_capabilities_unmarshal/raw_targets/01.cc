#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "TPM2.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  union.TPMU_CAPABILITIES target;
  int selector = stream.ConsumeIntegral<int>();
  int buffer_size = stream.ConsumeIntegralInRange<int>(0, size);
  std::string buffer_str = stream.ConsumeBytesAsString(buffer_size);
  char* buffer = const_cast<char*>(buffer_str.c_str());

  TPMU_CAPABILITIES_Unmarshal(&target, &buffer, &buffer_size, selector);

  return 0;
}