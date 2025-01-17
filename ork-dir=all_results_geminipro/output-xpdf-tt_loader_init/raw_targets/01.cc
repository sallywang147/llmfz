#include <fuzzer/FuzzedDataProvider.h>

#include <ft2build.h>
#include FT_FREETYPE_H

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
  FuzzedDataProvider fdp(data, size);
  int load_flags = fdp.ConsumeIntegralInRange<int>(0, 100);
  char glyf_table_only = fdp.ConsumeBool();

  FT_Library library;
  FT_Init_FreeType(&library);

  FT_Face face;
  FT_New_Memory_Face(library, data, size, 0, &face);

  FT_GlyphSlot slot = face->glyph;

  TT_Loader loader;
  TT_Size size;

  tt_loader_init(&loader, &size, slot, load_flags, glyf_table_only);

  FT_Done_Face(face);
  FT_Done_FreeType(library);

  return 0;
}