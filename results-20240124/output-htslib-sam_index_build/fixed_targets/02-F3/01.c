#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "../../htslib/sam.h"

extern "C" {
#include "Fuzzer.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);
  const size_t max_file_name_len = stream.ConsumeIntegralInRange<size_t>(1, 1024);
  char *file_name = static_cast<char*>(calloc(max_file_name_len + 1, sizeof(char)));
  stream.ConsumeBytesAsString(file_name, max_file_name_len);
  const int min_shift = stream.ConsumeIntegral<int>();
  sam_index_build(file_name, min_shift);
  free(file_name);
  return 0;
}