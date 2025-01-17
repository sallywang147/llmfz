#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <vector>

#include "tpm2-tss.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  TPMS_CAPABILITY_DATA target;
  std::vector<uint8_t> buffer_vec = stream.ConsumeRemainingBytes<uint8_t>();
  char* buffer = reinterpret_cast<char*>(buffer_vec.data());
  int buffer_size = buffer_vec.size();

  TPMS_CAPABILITY_DATA_Unmarshal(&target, &buffer, &buffer_size);

  return 0;
}