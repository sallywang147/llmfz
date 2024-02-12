#include <algorithm>

#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>

#include "TriCoreDisassembler.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const size_t handle = stream.ConsumeIntegral<size_t>();
  const size_t byte_len = stream.ConsumeIntegral<size_t>();
  const size_t address = stream.ConsumeIntegral<size_t>();

  char bytes[byte_len];
  stream.ConsumeBytes<char>(bytes, byte_len);

  char info[100];
  memset(info, 0, sizeof(info));

  struct MCInst mi;
  memset(&mi, 0, sizeof(mi));

  short size;

  bool result = TriCore_getInstruction(handle, bytes, byte_len, &mi, &size,
                                      address, info);

  return 0;
}