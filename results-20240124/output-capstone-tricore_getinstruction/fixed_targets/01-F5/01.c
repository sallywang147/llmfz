#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include <fuzzer/FuzzedDataProvider.h>
#include <mc/MCInst.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t handle = stream.ConsumeIntegral<size_t>();
  const size_t ByteLen = stream.ConsumeIntegral<size_t>();
  const size_t Address = stream.ConsumeIntegral<size_t>();
  std::vector<uint8_t> Bytes = stream.ConsumeBytes<uint8_t>(ByteLen);
  MCInst MI;
  short Size;
  std::string Info = stream.ConsumeRemainingBytesAsString();
  TriCore_getInstruction(handle, Bytes.data(), ByteLen, &MI, &Size, Address,
                         Info.c_str());
  return 0;
}