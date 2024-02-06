#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "ogs_gtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct ogs_gtp_xact_s xact;
  int teid = stream.ConsumeIntegral<int>();
  char type = stream.ConsumeIntegral<char>();
  char cause_value = stream.ConsumeIntegral<char>();

  ogs_gtp_send_error_message(&xact, teid, type, cause_value);

  return 0;
}