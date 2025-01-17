#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "libdwarf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  Dwarf_Debug_s dbg;
  Dwarf_Sig8_s ref;
  Dwarf_Die_s* die_out;
  int is_info;
  Dwarf_Error_s* error;

  // Consume data from the fuzzed input to initialize the parameters.
  if (stream.remaining_bytes() < sizeof(Dwarf_Debug_s)) {
    return 0;
  }
  stream.ConsumeData(&dbg, sizeof(Dwarf_Debug_s));

  if (stream.remaining_bytes() < sizeof(Dwarf_Sig8_s)) {
    return 0;
  }
  stream.ConsumeData(&ref, sizeof(Dwarf_Sig8_s));

  is_info = stream.ConsumeBool();

  // Call the function to fuzz
  dwarf_find_die_given_sig8(&dbg, &ref, &die_out, &is_info, &error);

  return 0;
}