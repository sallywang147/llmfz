#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

extern "C" {
#include "TriCore_Disassembler.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t handle = stream.ConsumeIntegral<size_t>();
  const size_t byte_len = stream.ConsumeIntegral<size_t>();
  std::vector<char> bytes(byte_len);
  stream.ConsumeBytes<char>(bytes.data(), byte_len);
  struct MCInst mi;
  memset(&mi, 0, sizeof(mi));
  short size;
  const size_t address = stream.ConsumeIntegral<size_t>();
  std::vector<char> info(stream.ConsumeRemainingBytes<char>());

  TriCore_getInstruction(handle, bytes.data(), byte_len, &mi, &size, address,
                         info.data());
  return 0;
}