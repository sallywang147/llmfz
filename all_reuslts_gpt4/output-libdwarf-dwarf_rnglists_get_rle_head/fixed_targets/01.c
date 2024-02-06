#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <vector>
#include "libdwarf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  // Initialize parameters
  struct Dwarf_Attribute_s attr;
  short theform = stream.ConsumeIntegral<short>();
  size_t attr_val = stream.ConsumeIntegral<size_t>();
  struct Dwarf_Rnglists_Head_s *head_out = nullptr;
  size_t entries_count_out = 0;
  size_t global_offset_of_rle_set = 0;
  struct Dwarf_Error_s *error = nullptr;

  // Consume data to populate the attribute struct
  if (stream.remaining_bytes() < sizeof(attr)) {
    return 0;
  }
  stream.ConsumeData(&attr, sizeof(attr));

  // Call the function to fuzz
  dwarf_rnglists_get_rle_head(&attr, theform, attr_val, &head_out, &entries_count_out, &global_offset_of_rle_set, &error);

  return 0;
}