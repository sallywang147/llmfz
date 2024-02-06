#include <fuzzer/FuzzedDataProvider.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

#include "dwarf.h"

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
  FuzzedDataProvider stream(data, size);

  struct Dwarf_Debug_s dbg;
  struct Dwarf_Rnglists_Head_s rctx;
  struct Dwarf_Error_s* error = nullptr;

  // Initialize the structures with data from the fuzzer
  if (stream.remaining_bytes() < sizeof(dbg) + sizeof(rctx))
    return 0;

  stream.ConsumeData(&dbg, sizeof(dbg));
  stream.ConsumeData(&rctx, sizeof(rctx));

  // Call the function to be fuzzed
  build_array_of_rle(&dbg, &rctx, &error);

  return 0;
}