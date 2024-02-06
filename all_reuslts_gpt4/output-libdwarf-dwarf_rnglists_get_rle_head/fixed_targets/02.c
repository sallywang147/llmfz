#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include "libdwarf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct Dwarf_Attribute_s attr;
  short theform = stream.ConsumeIntegral<short>();
  size_t attr_val = stream.ConsumeIntegral<size_t>();
  struct Dwarf_Rnglists_Head_s *head_out;
  size_t entries_count_out;
  size_t global_offset_of_rle_set;
  struct Dwarf_Error_s *error;

  // Initialize the attribute structure
  attr.at_form = theform;
  attr.at_value = attr_val;

  // Call the target function
  int ret = dwarf_rnglists_get_rle_head(&attr, theform, attr_val, &head_out, &entries_count_out, &global_offset_of_rle_set, &error);

  return 0;
}