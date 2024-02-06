#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ogs_gtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  ogs_gtp_xact_t xact;
  char recovery = stream.ConsumeIntegral<char>();

  ogs_gtp1_send_echo_response(&xact, recovery);

  return 0;
}