#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "dwarf.h"

extern "C" {
#include "dwarf_rnglists.h"
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct Dwarf_Attribute_s attr;
  attr.at_name = stream.ConsumeBytes<char>(stream.ConsumeIntegralInRange(0, 10));
  attr.at_form = stream.ConsumeIntegral<short>();
  attr.at_encoding = stream.ConsumeIntegral<short>();
  attr.at_type = stream.ConsumeIntegral<Dwarf_Half>();
  attr.at_sibling = stream.ConsumeIntegral<Dwarf_Half>();
  attr.at_byte_count = stream.ConsumeIntegral<Dwarf_Half>();
  attr.at_data = stream.ConsumeBytes<char>(stream.ConsumeIntegralInRange(0, 10));
  attr.at_next = nullptr;

  struct Dwarf_Rnglists_Head_s *head_out;
  size_t entries_count_out;
  size_t global_offset_of_rle_set;
  struct Dwarf_Error_s *error;

  dwarf_rnglists_get_rle_head(&attr, attr.at_form, 0, &head_out, &entries_count_out, &global_offset_of_rle_set, &error);
  dwarf_rnglists_free_rle_head(head_out);
  return 0;
}