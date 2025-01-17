#include <fuzzer/FuzzedDataProvider.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>

extern "C" {
#include <libdwarf/dwarf.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);
  struct Dwarf_Attribute_s attr;
  attr.at_name = stream.ConsumeRemainingBytesAsString().c_str();
  const short theform = stream.ConsumeIntegral<short>();
  const size_t attr_val = stream.ConsumeIntegral<size_t>();
  struct Dwarf_Rnglists_Head_s* head_out = nullptr;
  size_t entries_count_out = 0;
  size_t global_offset_of_rle_set = 0;
  struct Dwarf_Error_s* error = nullptr;

  dwarf_rnglists_get_rle_head(&attr, theform, attr_val, &head_out,
                              &entries_count_out, &global_offset_of_rle_set,
                              &error);
  if (head_out != nullptr) {
    dwarf_rnglists_head_free(head_out);
  }
  dwarf_error_free(error); // Call dwarf_error_free to free the error object
  return 0;
}