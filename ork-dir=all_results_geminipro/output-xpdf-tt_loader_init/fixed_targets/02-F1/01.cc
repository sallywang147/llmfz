#include <fuzzer/FuzzedDataProvider.h>

#include "ttload.h"

extern "C" {
#include <freetype/freetype.h>
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);

  TT_LoaderRec_ loader;
  TT_SizeRec_ size;
  FT_GlyphSlotRec_ glyph;

  int load_flags = fdp.ConsumeIntegral<int>();
  char glyf_table_only = fdp.ConsumeIntegral<char>();

  int result = tt_loader_init(&loader, &size, &glyph, load_flags, glyf_table_only);
  if (result) {
    return 0;
  }

  tt_loader_done(&loader);

  return 0;
}