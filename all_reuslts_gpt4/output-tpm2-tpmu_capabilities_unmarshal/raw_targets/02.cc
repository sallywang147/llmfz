#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>

#include "tpm2-tss.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  union.TPMU_CAPABILITIES target;
  int size_arg = stream.ConsumeIntegral<int>();
  int selector = stream.ConsumeIntegral<int>();

  std::string buffer_str = stream.ConsumeRemainingBytesAsString();
  char* buffer = const_cast<char*>(buffer_str.c_str());

  TPMU_CAPABILITIES_Unmarshal(&target, &buffer, &size_arg, selector);

  return 0;
}