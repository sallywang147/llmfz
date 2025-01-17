#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <string>

extern "C" {
#include "TriCore_getInstruction.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t handle = stream.ConsumeIntegral<size_t>();
  const size_t byte_len = stream.ConsumeIntegralInRange<size_t>(1, 16);
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(byte_len);
  struct MCInst mi;
  short size = 0;
  const size_t address = stream.ConsumeIntegral<size_t>();
  // Convert the std::string returned by ConsumeRemainingBytesAsString to a const char*
  const char* info = stream.ConsumeRemainingBytesAsString().c_str();

  TriCore_getInstruction(handle, reinterpret_cast<char*>(bytes.data()), byte_len,
                        &mi, &size, address, info);
  return 0;
}