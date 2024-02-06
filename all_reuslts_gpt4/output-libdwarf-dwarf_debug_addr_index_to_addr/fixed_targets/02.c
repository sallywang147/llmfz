#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <vector>

#include "libdwarf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Create a Dwarf_Die_s object
  Dwarf_Die_s die;
  size_t consumed = stream.ConsumeData(&die, sizeof(die));

  // If we could not consume enough data for the die, return early
  if (consumed != sizeof(die)) {
    return 0;
  }

  // Consume a size_t for the index
  size_t index = stream.ConsumeIntegral<size_t>();

  // Create a size_t for the return address and a Dwarf_Error_s for the error
  size_t return_addr;
  Dwarf_Error_s error;

  // Call the function to fuzz
  int result = dwarf_debug_addr_index_to_addr(&die, index, &return_addr, &error);

  return 0;
}