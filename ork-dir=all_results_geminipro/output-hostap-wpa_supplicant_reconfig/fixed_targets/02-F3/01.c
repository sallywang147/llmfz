#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>

#include <wpa_supplicant/wpa_supplicant.h> // Include the necessary header for wpa_supplicant_reconfig

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const int sig = stream.ConsumeIntegral<int>();
  const std::string signal_ctx = stream.ConsumeRemainingBytesAsString();

  wpa_supplicant_reconfig(sig, signal_ctx.c_str()); // Fix the function call by passing the correct argument type
  return 0;
}