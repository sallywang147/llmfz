#include <fuzzer/FuzzedDataProvider.h>
#include <algorithm>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <vector>

extern "C" {
#include <capstone/capstone.h>
#include <capstone/tricore.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t handle = stream.ConsumeIntegral<size_t>();
  const size_t byte_len = stream.ConsumeIntegral<size_t>();
  const size_t address = stream.ConsumeIntegral<size_t>();
  std::vector<char> bytes = stream.ConsumeBytes<char>(byte_len);
  struct MCInst mi;
  size_t size;
  char info[100];
  TriCore_getInstruction(handle, bytes.data(), byte_len, &mi, &size, address, info);
  return 0;
}