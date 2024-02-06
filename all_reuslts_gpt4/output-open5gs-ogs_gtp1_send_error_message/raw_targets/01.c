#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "ogs_gtp.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Extract integral values
  int teid = stream.ConsumeIntegral<int>();
  char type = stream.ConsumeIntegral<char>();
  char cause_value = stream.ConsumeIntegral<char>();

  // Extract to user defined object
  struct ogs_gtp_xact_s xact;
  size_t consumed = stream.ConsumeData(&xact, sizeof(xact));

  if (consumed != sizeof(xact)) {
    return 0;
  }

  ogs_gtp1_send_error_message(&xact, teid, type, cause_value);

  return 0;
}