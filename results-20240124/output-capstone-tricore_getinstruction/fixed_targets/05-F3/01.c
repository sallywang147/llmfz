#include <algorithm>
#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "TriCoreDisassembler.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  // handle is always 0 for TriCore
  const size_t handle = 0;
  const size_t byte_len = stream.ConsumeIntegral<size_t>();
  std::vector<uint8_t> bytes = stream.ConsumeBytes<uint8_t>(byte_len);
  struct MCInst mi;
  short size;
  const size_t address = stream.ConsumeIntegral<size_t>();
  std::string info = stream.ConsumeRandomLengthString();

  TriCore_getInstruction(handle, reinterpret_cast<char*>(bytes.data()), byte_len,
                        &mi, &size, address, info.c_str());
  return 0;
}