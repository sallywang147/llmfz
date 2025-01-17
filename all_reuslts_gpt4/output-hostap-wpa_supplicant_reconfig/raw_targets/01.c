#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "wpa_supplicant.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {

  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int sig = stream.ConsumeIntegral<int>();

  // Extract a string. You MUST use .c_str() to use result as pointer
  std::string signal_ctx = stream.ConsumeRandomLengthString();

  wpa_supplicant_reconfig(sig, const_cast<char *>(signal_ctx.c_str()));

  return 0;
}