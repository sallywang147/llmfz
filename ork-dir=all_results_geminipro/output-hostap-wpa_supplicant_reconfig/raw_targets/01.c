#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int signal = stream.ConsumeIntegral<int>();
  const std::string signal_ctx = stream.ConsumeRemainingBytesAsString();
  wpa_supplicant_reconfig(signal, const_cast<char*>(signal_ctx.c_str()));
  return 0;
}