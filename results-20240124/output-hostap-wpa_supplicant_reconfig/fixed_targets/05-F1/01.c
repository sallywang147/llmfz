#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

extern "C" {
#include "wpa_supplicant/wpa_supplicant.h"
#include "wpa_fuzzer/wpa_fuzzer.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  const int sig = stream.ConsumeIntegral<int>();
  const std::string signal_ctx = stream.ConsumeRemainingBytesAsString();

  wpa_supplicant_reconfig(sig, const_cast<char*>(signal_ctx.c_str()));

  return 0;
}