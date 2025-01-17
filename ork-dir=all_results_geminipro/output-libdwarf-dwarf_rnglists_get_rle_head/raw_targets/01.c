#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "dwarf.h"

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
  attr.at_next = stream.ConsumeIntegral<Dwarf_Off>();

  struct Dwarf_Rnglists_Head_s* head_out = nullptr;
  size_t entries_count_out = 0;
  size_t global_offset_of_rle_set = 0;
  struct Dwarf_Error_s* error = nullptr;
  dwarf_rnglists_get_rle_head(&attr, attr.at_form, attr.at_byte_count, &head_out,
                             &entries_count_out, &global_offset_of_rle_set,
                             &error);
  return 0;
}