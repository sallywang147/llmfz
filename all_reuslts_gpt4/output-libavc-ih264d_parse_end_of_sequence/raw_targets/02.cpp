#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

#include "ih264d.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  
  // Initialize DecStruct
  struct _DecStruct ps_dec;
  
  // Consume data to fill DecStruct
  size_t consumed = stream.ConsumeData(&ps_dec, sizeof(ps_dec));

  // If not enough data to fill DecStruct, return early
  if(consumed != sizeof(ps_dec)) {
    return 0;
  }

  // Call the target function
  int result = ih264d_parse_end_of_sequence(&ps_dec);

  return 0;
}