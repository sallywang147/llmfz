#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "parallel_hashmap/phmap.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Consume the remaining bytes as a string
  std::string ctrl_str = stream.ConsumeRemainingBytesAsString();

  // Convert the string to a char array
  char* ctrl = strdup(ctrl_str.c_str());

  // Call the function to fuzz
  phmap::priv::ConvertDeletedToEmptyAndFullToDeleted(ctrl, ctrl_str.size());

  // Free the allocated memory
  free(ctrl);

  return 0;
}