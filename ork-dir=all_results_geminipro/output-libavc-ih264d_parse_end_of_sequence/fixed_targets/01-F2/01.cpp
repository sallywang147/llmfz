#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include "ih264d_parse.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct _DecStruct decoder;
  ih264d_init_decoder(&decoder);
  ih264d_parse_end_of_sequence(&decoder);
  ih264d_free_decoder(&decoder);
  return 0;
}