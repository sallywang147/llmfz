#include <inttypes.h>
#include <stdlib.h>

#include <llvm/MC/MCInst.h>

#include "TriCore.h"
#include "fuzzer/FuzzedDataProvider.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  size_t handle = stream.ConsumeIntegral<size_t>();
  size_t ByteLen = stream.ConsumeIntegralInRange<size_t>(1, size);
  size_t Address = stream.ConsumeIntegral<size_t>();

  std::string Bytes = stream.ConsumeBytesAsString(ByteLen);
  std::string Info = stream.ConsumeRandomLengthString();

  MCInst MI;
  short Size;

  TriCore_getInstruction(handle, const_cast<char*>(Bytes.c_str()), ByteLen, &MI, &Size, Address, const_cast<char*>(Info.c_str()));

  return 0;
}